#include "config.hpp"

ActuatorMessage build_safe_state(const ActuatorMessage &current_state) {
  return ActuatorMessage{
<<<<<<< HEAD
      .ov101 = false,
      .ov102 = false,
      .ov103 = false,
      .nv201 = false,
      .cdv401 = false,
      .cdv402 = false,
      .qd301 = false,
      .pyro_valve = false,
      .rocket_charging = false,
=======
      .v305 = false,
      .v301 = false,
      .v405 = false,
>>>>>>> 4633435 (Initial E-Pump spin test RLCS config)
      .tank_heating_1 = false,
      .tank_heating_2 = false,
      .ignition_primary = false,
      .ignition_secondary = false,
  };
}
