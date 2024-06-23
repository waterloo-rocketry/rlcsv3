#include "config.hpp"

ActuatorMessage build_safe_state(const ActuatorMessage &current_state) {
  return ActuatorMessage{
      .ov101 = false,
      .ov102 = false,
      .nv101 = false,
      .nv102 = true,
	  .fill_disconnect = current_state.fill_disconnect,
	  .rocket_power = current_state.rocket_power,
      .ignition_primary = false,
      .ignition_secondary = false,
  };
}
