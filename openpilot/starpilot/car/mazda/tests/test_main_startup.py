from dataclasses import replace

import pytest
from opendbc.car import gen_empty_fingerprint, structs
from opendbc.car.mazda.interface import CarInterface
from opendbc.car.mazda.values import CAR
from openpilot.starpilot.aol.intent import AolSettings
from openpilot.starpilot.car.mazda.stock_intent import MazdaStockCardIntent


@pytest.mark.parametrize('identity', (CAR.MAZDA_CX5_2022, CAR.MAZDA_CX9_2021))
@pytest.mark.parametrize('blocker', ('disabled', 'main_toggle', 'lkas_toggle', 'active', 'permanent', 'fault'))
def test_startup_main_never_overrides_saved_off_or_disarming_fault(identity, blocker):
  cp = CarInterface.get_params(identity, gen_empty_fingerprint(), [], False, False, False)
  settings = AolSettings(True, 0., 0, 0, (0, 0, 0), (0, 0, 0))
  if blocker == 'disabled':
    settings = replace(settings, enabled=False)
  elif blocker == 'main_toggle':
    settings = replace(settings, main_action=9)
  elif blocker == 'lkas_toggle':
    settings = replace(settings, lkas_action=9)
  intent = MazdaStockCardIntent(cp, settings)
  cs = structs.CarState(canValid=True, gearShifter='drive')
  cs.cruiseState.available = True
  cs.cruiseState.enabled = blocker == 'active'
  cs.steerFaultPermanent = blocker == 'permanent'
  intent.update(cs.as_reader(), fault_active=blocker == 'fault', now_ns=1_000_000_000)
  assert not intent.allowed_latch
  cs.cruiseState.enabled = False
  cs.steerFaultPermanent = False
  for tick in range(10):
    intent.update(cs.as_reader(), fault_active=False, now_ns=1_010_000_000 + tick * 10_000_000)
    assert not intent.allowed_latch


@pytest.mark.parametrize('identity', (CAR.MAZDA_CX5_2022, CAR.MAZDA_CX9_2021))
def test_invalid_can_cannot_supply_startup_main(identity):
  cp = CarInterface.get_params(identity, gen_empty_fingerprint(), [], False, False, False)
  intent = MazdaStockCardIntent(cp, AolSettings(True, 0., 0, 0, (0, 0, 0), (0, 0, 0)))
  cs = structs.CarState(canValid=False, canTimeout=True)
  cs.cruiseState.available = True
  intent.update(cs.as_reader(), fault_active=False, now_ns=1_000_000_000)
  assert not intent.allowed_latch and intent.startup_main_pending


@pytest.mark.parametrize('bad', ('none', 'producer', 'session', 'future', 'expired', 'unacknowledged',
                                 'active', 'native_request', 'panda_fault', 'axis_invalid', 'events_stale'))
def test_startup_admission_requires_bound_current_idle_proof(bad):
  from openpilot.starpilot.tests.test_ford_reverse_intent import NOW, PRODUCER, change, native_change, sample

  cp = CarInterface.get_params(CAR.MAZDA_CX5_2022, gen_empty_fingerprint(), [], False, False, False)
  cp.alternativeExperience = 32
  intent = MazdaStockCardIntent(cp, AolSettings(True, 0., 0, 0, (0, 0, 0), (0, 0, 0)))
  cs = structs.CarState(canValid=True, gearShifter='drive')
  cs.cruiseState.available = True
  for tick in range(1, 4):
    now = NOW + tick * 10_000_000
    sm, native = sample(cp, now, now, tick, active=False, requested=False, allowed=False, event_stamp=now)
    producer = PRODUCER
    if bad == 'producer':
      producer = 'other-card'
    elif bad == 'session':
      change(sm, 'aolAxisState', lambda axis: setattr(axis, 'sessionId', 'other-axis'))
    elif bad == 'future':
      change(sm, 'aolAxisState', lambda axis, stamp=now: setattr(axis, 'sourceCarStateMonoTime', stamp + 1))
    elif bad == 'expired':
      change(sm, 'aolAxisState', lambda axis, stamp=now: setattr(axis, 'validUntilMonoTime', stamp - 1))
    elif bad == 'unacknowledged':
      change(sm, 'aolAxisState', lambda axis: setattr(axis, 'nativeAcknowledged', False))
    elif bad == 'active':
      change(sm, 'aolAxisState', lambda axis: setattr(axis, 'lateralActive', True))
    elif bad == 'native_request':
      native = native_change(sm, native, requestedLateral=True)
    elif bad == 'panda_fault':
      change(sm, 'pandaStates', lambda pandas: setattr(pandas[0], 'safetyRxChecksInvalid', True))
    elif bad == 'axis_invalid':
      sm.valid['aolAxisState'] = False
    elif bad == 'events_stale':
      sm.logMonoTime['onroadEvents'] = now - 1_500_000_001
    intent.observe_startup_readiness(sm, cs, native=native, panda_ready=True, now_ns=now, producer=producer)
    intent.update(cs.as_reader(), fault_active=False, now_ns=now)
  assert intent.allowed_latch is (bad == 'none')
  assert not native.lateralAllowed and not native.longitudinalAllowed



def test_main_on_arms_lateral_without_engaging_acc():
  from openpilot.starpilot.tests.test_ford_reverse_intent import NOW, PRODUCER, sample

  cp = CarInterface.get_params(CAR.MAZDA_CX5_2022, gen_empty_fingerprint(), [], False, False, False)
  cp.alternativeExperience = 32
  intent = MazdaStockCardIntent(cp, AolSettings(True, 0., 0, 0, (0, 0, 0), (0, 0, 0)))
  cs = structs.CarState(canValid=True, gearShifter='drive')
  cs.cruiseState.available = False
  cs.cruiseState.enabled = False

  # With stock MAIN/ACC off, startup authorization must wait for the driver.
  intent.update(cs.as_reader(), fault_active=False, now_ns=NOW)
  assert intent.startup_main_pending
  assert not intent.allowed_latch

  # Pressing MAIN makes cruise available. Two fresh, idle native proofs are
  # still required before independent lateral arming is admitted.
  cs.cruiseState.available = True
  for tick in (1, 2, 3):
    now = NOW + tick * 10_000_000
    sm, native = sample(cp, now, now, tick, active=False, requested=False, allowed=False, event_stamp=now)
    intent.observe_startup_readiness(sm, cs, native=native, panda_ready=True, now_ns=now, producer=PRODUCER)
    intent.update(cs.as_reader(), fault_active=False, now_ns=now)
  assert intent.allowed_latch
  assert not intent.startup_main_pending
  assert not cs.cruiseState.enabled
  assert not native.lateralAllowed and not native.longitudinalAllowed


def test_cx8_ti1_profile_is_admitted_only_with_exact_safety_configuration():
  from opendbc.car.mazda.stock_aol import admitted
  from opendbc.car.mazda.values import MazdaSafetyFlags

  cp = CarInterface.get_params(CAR.MAZDA_CX8, gen_empty_fingerprint(), [], False, False, False)
  ti1_param = int(MazdaSafetyFlags.GEN1 | MazdaSafetyFlags.TORQUE_INTERCEPTOR)
  cp.flags = ti1_param
  cp.safetyConfigs[0].safetyParam = ti1_param
  cp.alternativeExperience = 32
  assert admitted(cp, marked_only=True)

  cp.safetyConfigs[0].safetyParam = 0
  assert not admitted(cp, marked_only=True)


def test_temporary_restriction_release_grace_is_bounded():
  from opendbc.car.mazda.stock_aol import RESTRICTION_RELEASE_GRACE_NS, within_restriction_grace

  released_at = 1_000_000_000
  assert within_restriction_grace(released_at, released_at)
  assert within_restriction_grace(released_at, released_at + RESTRICTION_RELEASE_GRACE_NS)
  assert not within_restriction_grace(released_at, released_at + RESTRICTION_RELEASE_GRACE_NS + 1)
  assert not within_restriction_grace(0, released_at)
