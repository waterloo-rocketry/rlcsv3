#include "config.hpp"

ActuatorMessage build_safe_state(const ActuatorMessage &current_state) {
  return ActuatorMessage{
      .valve_1 = false,
      .valve_2 = true,
      .valve_3 = false,
      .vent_valve = true,
      .injector_valve = current_state.injector_valve,
      .ignition_primary = false,
      .ignition_secondary = false,
  };
}

