from opendbc.can import CANPacker
from opendbc.car import Bus, structs
from opendbc.car.lateral import apply_driver_steer_torque_limits
from opendbc.car.interfaces import CarControllerBase
from opendbc.car.mazda import mazdacan
from opendbc.car.mazda.longitudinal import CAM_BUS, LONG_COMMAND_STEP, NEAR_STOP_ENTRY_SPEED, RADAR_BUS, \
                                           RADAR_HEARTBEAT_STEP, TESTER_PRESENT_STEP, \
                                           create_longitudinal_messages, create_radar_heartbeat_messages, \
                                           create_radar_tester_present, hold_brake_accel, hold_latched_accel, \
                                           near_stop_brake_accel
from opendbc.car.mazda.values import CarControllerParams, Buttons, MazdaSafetyFlags
from openpilot.common.realtime import DT_CTRL
from openpilot.common.filter_simple import FirstOrderFilter
from openpilot.common.params import Params

VisualAlert = structs.CarControl.HUDControl.VisualAlert
LongCtrlState = structs.CarControl.Actuators.LongControlState

# radar emulation stop-and-go phase timings
CRZ_CTRL_LATCH_FRAMES = int(round(2.0 / DT_CTRL))
CRZ_CTRL_PASSIVE_FRAMES = int(round(9.6 / DT_CTRL))
CRZ_CTRL_RESUME_REACTIVATE_FRAMES = int(round(0.08 / DT_CTRL))
CRZ_INFO_RESUME_PHASE_FRAMES = int(round(0.20 / DT_CTRL))
HOLD_REQUEST_FRAMES = int(round(6.0 / DT_CTRL))
RESUME_RELEASE_FRAMES = int(round(0.5 / DT_CTRL))

# TI driver handover: release immediately while the driver is applying steering,
# then wait 100 ms after release before returning authority to OP + TI.
DRIVER_TAKEOVER_DELAY_FRAMES = int(round(0.1 / DT_CTRL))

class CarController(CarControllerBase):
  def __init__(self, dbc_names, CP):
    super().__init__(dbc_names, CP)
    self.apply_torque_last = 0
    self.ti_apply_torque_last = 0
    self.packer = CANPacker(dbc_names[Bus.pt])
    self.brake_counter = 0
    self.ccp = CarControllerParams(CP)
    self.hold_timer_frame = 0
    self.hold_delay_frame = 0
    self.resume_timer_frame = 0
    self.acc_filter = FirstOrderFilter(0.0, .1, DT_CTRL, initialized=False)
    self.filtered_acc_last = 0
    self.long_active_last = False
    # radar emulation state
    self.long_counter = 0
    self.radar_counter = 0
    self.standstill_hold_frames = 0
    self.stop_intent_latched = False
    self.resume_release_frames = 0
    self.resume_crz_latched_frames = 0
    self.resume_phase_frames = 0
    self.resume_ctrl_active_prev = False
    self.virtual_resume_sent_latched = False
    self.resume_button_prev = False
    self.emu_session = False
    # TI driver handover state. This does not change TI state/RUN status.
    self.driver_takeover = False
    self.driver_takeover_delay_frames = 0
    self.params = Params()
    self.params_memory = Params("/dev/shm/params")



  def update(self, CC, CS, now_nanos, starpilot_toggles):
    can_sends = []

    apply_torque = 0
    ti_apply_torque = 0

    # Driver-touch handover is based on the existing TI steering-touch signal.
    # While touched, suppress both OP and TI steering output without changing
    # TI feedback state, so TI can remain RUN. After release, wait exactly 100 ms
    # and then immediately return authority to OP + TI, subject to normal torque limits.
    if self.CP.flags & MazdaSafetyFlags.TORQUE_INTERCEPTOR:
      driver_touch = bool(CS.out.steeringPressed)
      if driver_touch:
        self.driver_takeover = True
        self.driver_takeover_delay_frames = DRIVER_TAKEOVER_DELAY_FRAMES
      elif self.driver_takeover:
        if self.driver_takeover_delay_frames > 0:
          self.driver_takeover_delay_frames -= 1
        else:
          self.driver_takeover = False

    if CC.latActive:
      # calculate steer and also set limits due to driver torque
      new_torque = int(round(CC.actuators.torque * self.ccp.STEER_MAX))
      apply_torque = apply_driver_steer_torque_limits(new_torque, self.apply_torque_last,
                                                      CS.out.steeringTorque, self.ccp)
      if self.CP.flags & MazdaSafetyFlags.TORQUE_INTERCEPTOR:
        if CS.ti_lkas_allowed:
          ti_new_torque = int(round(CC.actuators.torque * self.ccp.STEER_MAX))
          ti_apply_torque = apply_driver_steer_torque_limits(ti_new_torque, self.apply_torque_last,
                                                    CS.out.steeringTorque, self.ccp)

    if self.driver_takeover:
      apply_torque = 0
      ti_apply_torque = 0

    self.apply_torque_last = apply_torque
    self.ti_apply_torque_last = ti_apply_torque

    if self.CP.flags & MazdaSafetyFlags.GEN1:
      radar_emulation = bool(self.CP.flags & MazdaSafetyFlags.RADAR_EMULATION)
      virtual_resume_sent = False

      if radar_emulation:
        if CC.longActive:
          self.emu_session = True
        self.brake_counter = 0
        if CS.out.standstill and CC.cruiseControl.resume and self.frame % 5 == 0:
          can_sends.append(mazdacan.create_button_cmd(self.packer, self.CP, CS.crz_btns_counter, Buttons.RESUME))
          virtual_resume_sent = True
      elif CC.cruiseControl.cancel:
        self.brake_counter = self.brake_counter + 1
        if self.frame % 10 == 0 and not (CS.out.brakePressed and self.brake_counter < 7):
          can_sends.append(mazdacan.create_button_cmd(self.packer, self.CP, CS.crz_btns_counter, Buttons.CANCEL))
      elif not radar_emulation:
        self.brake_counter = 0
        if CC.cruiseControl.resume and self.frame % 5 == 0:
          can_sends.append(mazdacan.create_button_cmd(self.packer, self.CP, CS.crz_btns_counter, Buttons.RESUME))

      # send HUD alerts
      if self.frame % 50 == 0:
        ldw = CC.hudControl.visualAlert == VisualAlert.ldw
        steer_required = CC.hudControl.visualAlert == VisualAlert.steerRequired
        steer_required = steer_required and CS.lkas_allowed_speed
        can_sends.append(mazdacan.create_alert_command(self.packer, CS.cam_laneinfo, ldw, steer_required))

      if radar_emulation:
        stopping = CC.actuators.longControlState == LongCtrlState.stopping
        starting = CC.actuators.longControlState == LongCtrlState.starting
        restart_requested = starting
        if not CC.cruiseControl.resume or not CS.out.standstill:
          self.virtual_resume_sent_latched = False
        elif virtual_resume_sent:
          self.virtual_resume_sent_latched = True
        physical_resume_requested = bool(CS.accel_button)
        virtual_resume_requested = CC.cruiseControl.resume and self.virtual_resume_sent_latched
        effective_resume_requested = False
        release_hold_requested = False
        release_brake = False
        stop_go_release_requested = False
        if not CC.longActive:
          self.standstill_hold_frames = 0
          self.stop_intent_latched = False
          self.resume_release_frames = 0
          self.resume_crz_latched_frames = 0
          self.resume_phase_frames = 0
          self.resume_ctrl_active_prev = False
          self.virtual_resume_sent_latched = False
        else:
          if stopping:
            self.stop_intent_latched = True

          hold_latched_ready = CS.out.standstill and self.standstill_hold_frames > HOLD_REQUEST_FRAMES
          physical_resume_unlatch_requested = CS.out.standstill and physical_resume_requested and (not stopping or hold_latched_ready)
          virtual_resume_unlatch_requested = CS.out.standstill and virtual_resume_requested and hold_latched_ready
          resume_unlatch_requested = physical_resume_unlatch_requested or virtual_resume_unlatch_requested
          effective_resume_requested = resume_unlatch_requested
          resume_rising_edge = effective_resume_requested and not self.resume_button_prev
          release_brake = self.resume_release_frames > 0
          base_release_hold_requested = CC.cruiseControl.override or CS.out.gasPressed or restart_requested or release_brake

          if CS.out.standstill and self.stop_intent_latched and not base_release_hold_requested:
            self.standstill_hold_frames += 1
          else:
            self.standstill_hold_frames = 0

          if CS.out.standstill and not base_release_hold_requested and resume_rising_edge and self.standstill_hold_frames >= CRZ_CTRL_PASSIVE_FRAMES:
            self.resume_crz_latched_frames = CRZ_CTRL_RESUME_REACTIVATE_FRAMES
          elif self.resume_crz_latched_frames > 0:
            self.resume_crz_latched_frames -= 1

          if resume_unlatch_requested:
            self.resume_release_frames = RESUME_RELEASE_FRAMES
          elif self.resume_release_frames > 0:
            self.resume_release_frames -= 1

          release_brake = self.resume_release_frames > 0
          release_hold_requested = base_release_hold_requested or resume_unlatch_requested or release_brake
          stop_go_release_requested = self.stop_intent_latched and release_hold_requested

          if release_hold_requested or (not CS.out.standstill and not stopping and CS.out.vEgo > NEAR_STOP_ENTRY_SPEED):
            self.stop_intent_latched = False

        stop_go_request = CC.longActive and self.stop_intent_latched and not release_hold_requested
        standstill_hold_request = stop_go_request and CS.out.standstill
        hold_latched = standstill_hold_request and self.standstill_hold_frames > HOLD_REQUEST_FRAMES
        brake_release_requested = release_hold_requested or effective_resume_requested

        crz_hold_latched = standstill_hold_request and self.standstill_hold_frames >= CRZ_CTRL_LATCH_FRAMES and \
                           (not effective_resume_requested or self.resume_crz_latched_frames > 0)
        crz_hold_passive = standstill_hold_request and self.standstill_hold_frames >= CRZ_CTRL_PASSIVE_FRAMES and not effective_resume_requested
        release_brake = self.resume_release_frames > 0
        crz_ctrl_resume_active = release_brake and CS.out.vEgo < self.CP.vEgoStarting and not crz_hold_latched and not crz_hold_passive
        if crz_ctrl_resume_active:
          if not self.resume_ctrl_active_prev:
            self.resume_phase_frames = CRZ_INFO_RESUME_PHASE_FRAMES
          elif self.resume_phase_frames > 0:
            self.resume_phase_frames -= 1
        else:
          self.resume_phase_frames = 0
        crz_info_resume_unlatching = crz_ctrl_resume_active and self.resume_phase_frames > 0
        self.resume_ctrl_active_prev = crz_ctrl_resume_active
        crz_info_hold_request = stop_go_request and not (brake_release_requested or release_brake)

        accel = 0.0
        if CC.longActive:
          accel = CC.actuators.accel
          if release_brake:
            accel = max(accel, 0.0)
          elif CS.out.standstill:
            accel = hold_latched_accel() if hold_latched else hold_brake_accel()
          elif self.stop_intent_latched and not release_hold_requested and (stopping or CS.out.vEgo < NEAR_STOP_ENTRY_SPEED):
            accel = min(accel, near_stop_brake_accel(CS.out.vEgo))

        if self.emu_session and self.frame % TESTER_PRESENT_STEP == 0:
          can_sends.append(create_radar_tester_present(RADAR_BUS))

        lead_visible = CC.hudControl.leadVisible
        synthetic_radar_lead = CC.longActive and (lead_visible or stop_go_request or standstill_hold_request or hold_latched or
                                                  crz_hold_latched or crz_hold_passive or crz_ctrl_resume_active or
                                                  stop_go_release_requested or release_brake or starting)
        if self.emu_session and self.frame % RADAR_HEARTBEAT_STEP == 0:
          for bus in (RADAR_BUS, CAM_BUS):
            can_sends.extend(create_radar_heartbeat_messages(bus, self.radar_counter, synthetic_lead=synthetic_radar_lead))
          self.radar_counter = (self.radar_counter + 1) % 16

        if self.emu_session and self.frame % LONG_COMMAND_STEP == 0:
          for bus in (RADAR_BUS, CAM_BUS):
            can_sends.extend(create_longitudinal_messages(bus, accel, self.long_counter,
                                                          CC.longActive, lead_visible,
                                                          hold_request=crz_info_hold_request,
                                                          crz_ctrl_hold_request=stop_go_request,
                                                          hold_latched=hold_latched,
                                                          crz_hold_latched=crz_hold_latched,
                                                          crz_hold_passive=crz_hold_passive,
                                                          crz_resume_active=crz_ctrl_resume_active,
                                                          crz_info_resume_unlatching=crz_info_resume_unlatching,
                                                          crz_available=CS.out.cruiseState.available,
                                                          v_ego=CS.out.vEgo))
          self.long_counter = (self.long_counter + 1) % 16
        self.resume_button_prev = effective_resume_requested
      elif self.CP.openpilotLongitudinalControl:
        hold = False
        if CS.out.standstill:
          hold = (self.frame - self.hold_timer_frame) < 600
        else:
          self.hold_timer_frame = self.frame

          stock_acc = CS.crz_info["ACCEL_CMD"]
          op_acc = CC.actuators.accel * 1150
          op_acc = max(-1000, min(op_acc, 1000))

          if self.params.get_bool("BlendedACC"):
            if CC.longActive:
              if not self.long_active_last:
                self.acc_filter.initialized = False
              target_acc = op_acc if self.params_memory.get_int("CEStatus") != 0 else stock_acc
              acc_output = self.acc_filter.update(target_acc)
            else:
              acc_output = stock_acc
          else:
            acc_output = op_acc

          acc_output = max(-1000, min(acc_output, 1000))
          CS.crz_info["ACCEL_CMD"] = acc_output

        if self.frame % 2 == 0:
          can_sends.extend(mazdacan.create_radar_command(self.packer, self.frame, CC.longActive, CS, hold))

    elif self.CP.flags & MazdaSafetyFlags.GEN2:
      if self.CP.openpilotLongitudinalControl:
        stock_acc = CS.acc["ACCEL_CMD"]
        op_acc = (CC.actuators.accel * 200) + 2000

        if self.params.get_bool("BlendedACC"):
          if CC.longActive:
            if not self.long_active_last:
              self.acc_filter.initialized = False
            target_acc = op_acc if self.params_memory.get_int("CEStatus") != 0 else stock_acc
            acc_output = self.acc_filter.update(target_acc)
          else:
            acc_output = stock_acc
        else:
          acc_output = op_acc if CC.longActive else stock_acc

        CS.acc["ACCEL_CMD"] = acc_output

      resume = False
      hold = False
      if self.frame % 2 == 0:
        """
        Without this hold/resum logic, the car will only stop momentarily.
        It will then start creeping forward again. This logic allows the car to
        apply the electric brake to hold the car. The hold delay also fixes a
        bug with the stock ACC where it sometimes will apply the brakes too early
        when coming to a stop.
        """
        if CS.out.standstill:
          if not ((self.frame - self.hold_delay_frame) < 50):
            if ((CC.cruiseControl.resume and CC.actuators.longControlState != LongCtrlState.stopping) or
                CC.cruiseControl.override or CS.out.gasPressed or
                (CC.actuators.longControlState == LongCtrlState.starting) or CS.acc["RESUME"]):
              self.resume_timer_frame = self.frame
            else:
              hold = (self.frame - self.hold_timer_frame) < 600

        else:
          self.hold_timer_frame = self.frame
          self.hold_delay_frame = self.frame

        resume = (self.frame - self.resume_timer_frame) < 50
        can_sends.append(mazdacan.create_acc_cmd(self.packer, CS.acc, hold, resume))


    # send steering command
    can_sends.extend(mazdacan.create_steering_control(
      self.packer, self.CP, self.frame, apply_torque, CS.cam_lkas,
      ti_apply_torque if self.CP.flags & MazdaSafetyFlags.TORQUE_INTERCEPTOR else None))

    new_actuators = CC.actuators.as_builder()
    new_actuators.torque = apply_torque / self.ccp.STEER_MAX
    new_actuators.torqueOutputCan = apply_torque

    self.long_active_last = CC.longActive
    self.frame += 1
    return new_actuators, can_sends