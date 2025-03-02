#include "config.hpp"

ActuatorMessage build_safe_state(const ActuatorMessage &current_state) {
  return ActuatorMessage{
      .ov101 = false,
      .ov102 = true,
      .ov103 = true,
      .nv201 = false,
      .injector_valve = current_state.injector_valve,
      .tank_heating_1 = false,
      .tank_heating_2 = false,
      .ignition_primary = false,
      .ignition_secondary = false,
  };
}
