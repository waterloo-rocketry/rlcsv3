#include "config.hpp"

ActuatorMessage build_safe_state(const ActuatorMessage &current_state) {
  return ActuatorMessage{
      .ov101 = false,
      .ov102 = false,
      .nv101 = false,
      .ov201 = true,
	  .ov202 = true,
      .injector_valve = current_state.injector_valve,
      .ignition_primary = false,
      .ignition_secondary = false,
  };
}
