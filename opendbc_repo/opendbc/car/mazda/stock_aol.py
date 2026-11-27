from opendbc.car import structs
from opendbc.car.mazda.values import CAR, MazdaSafetyFlags

CARS = frozenset((CAR.MAZDA_CX5_2022, CAR.MAZDA_CX9_2021))


def qualified(cp, *, marked_only=False):
  return (cp.brand == "mazda" and cp.carFingerprint in CARS and int(cp.flags) == int(MazdaSafetyFlags.GEN1) and
          not cp.passive and not cp.notCar and not cp.dashcamOnly and
          cp.transmissionType != structs.CarParams.TransmissionType.manual and
          cp.fingerprintSource != structs.CarParams.FingerprintSource.fixed and
          cp.pcmCruise and not cp.openpilotLongitudinalControl and len(cp.safetyConfigs) == 1 and
          cp.safetyConfigs[0].safetyModel == structs.CarParams.SafetyModel.mazda and
          cp.safetyConfigs[0].safetyParam == 0 and cp.alternativeExperience in ((32,) if marked_only else (0, 32)))



# GEN1 Torque Interceptor (TI1) AOL admission is separate from stock GEN1.
TI1_CARS = frozenset((CAR.MAZDA_CX8,))
TI1_AOL_SAFETY_PARAM = int(MazdaSafetyFlags.GEN1 | MazdaSafetyFlags.TORQUE_INTERCEPTOR)
TI1_EVIDENCE_GATES = {
  # CX-8 TI1 signal evidence: 0x21C MAIN, 0x228 gear, 0x243 camera status;
  # TI_FEEDBACK liveness replaces the stock EPS 0x241 lockout bit.
  'cx8_signals': True,
}


def _only_safety_config_is(cp, param):
  configs = cp.safetyConfigs
  if len(configs) != 1:
    return False
  config = configs[0]
  return config.safetyModel == structs.CarParams.SafetyModel.mazda and config.safetyParam == param


def ti1_configuration(cp, *, marked_only=False):
  return (cp.brand == "mazda" and cp.carFingerprint in TI1_CARS and
          int(cp.flags) == TI1_AOL_SAFETY_PARAM and
          not cp.passive and not cp.notCar and not cp.dashcamOnly and
          cp.transmissionType == structs.CarParams.TransmissionType.automatic and
          cp.fingerprintSource != structs.CarParams.FingerprintSource.fixed and
          cp.pcmCruise and not cp.openpilotLongitudinalControl and
          _only_safety_config_is(cp, TI1_AOL_SAFETY_PARAM) and
          cp.alternativeExperience in ((32,) if marked_only else (0, 32)))


def ti1_qualified(cp, gates=TI1_EVIDENCE_GATES, *, marked_only=False):
  return bool(gates.keys() == TI1_EVIDENCE_GATES.keys() and all(gates.values()) and
              ti1_configuration(cp, marked_only=marked_only))


def admitted(cp, *, marked_only=False):
  return qualified(cp, marked_only=marked_only) or ti1_qualified(cp, marked_only=marked_only)


# A Panda denial can arrive up to the safety-state freshness window late after
# a temporary restriction ends. Suppress only that short stale-rejection window.
RESTRICTION_RELEASE_GRACE_NS = 250_000_000


def within_restriction_grace(restricted_ns, now_ns):
  return bool(restricted_ns and 0 <= now_ns - restricted_ns <= RESTRICTION_RELEASE_GRACE_NS)


def temporary_restriction(cp, state):
  return bool(state is not None and admitted(cp, marked_only=True) and state.canValid and not state.canTimeout and
              not state.steerFaultPermanent and (state.gearShifter != structs.CarState.GearShifter.drive or
                                                 state.steerFaultTemporary or state.standstill or (cp.minSteerSpeed > 0 and state.vEgo < cp.minSteerSpeed)))


def native_observation(native, *, latched, panda_ready, restricted, now_ns, pending_since_ns):
  lost = not panda_ready or native is None
  if not latched or lost or restricted:
    return 0, lost, False
  if native.requestedLateral and native.lateralAllowed:
    return 0, False, False
  pending_since_ns = pending_since_ns or now_ns
  return pending_since_ns, False, now_ns - pending_since_ns >= 200_000_000
