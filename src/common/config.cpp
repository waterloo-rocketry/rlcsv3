#include "config.hpp"

ActuatorMessage build_safe_state(const ActuatorMessage &current_state) {
  return ActuatorMessage{
      .ov101 = false,
      .ov102 = true,
      .ov103 = true,
      .injector_valve = current_state.injector_valve,
      .tank_heating_1 = false,
      .tank_heating_2 = false,
      .sequence_a = false,
      .sequence_b = false,
      .start_sequence = false,
  };
}
