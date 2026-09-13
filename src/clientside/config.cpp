#include "config.hpp"
#include "common/mock_arduino.hpp"
#include "pinout.hpp"

namespace config {

ActuatorMessage build_command_message() {
  return ActuatorMessage{
<<<<<<< HEAD
      .ov101 = digitalRead(pinout::MISSILE_SWITCH_1),
      .ov102 = digitalRead(pinout::MISSILE_SWITCH_2),
      .ov103 = digitalRead(pinout::MISSILE_SWITCH_3),
      .nv201 = digitalRead(pinout::MISSILE_SWITCH_4),
      .cdv401 = digitalRead(pinout::MISSILE_SWITCH_5),
      .cdv402 = digitalRead(pinout::MISSILE_SWITCH_6),
      .qd301 = digitalRead(pinout::MISSILE_SWITCH_IGNITION_SEC),
      .pyro_valve = digitalRead(pinout::MISSILE_SWITCH_INJECTOR),
      .rocket_charging = digitalRead(pinout::MISSILE_SWITCH_7),
=======
      .v305 = digitalRead(pinout::MISSILE_SWITCH_1),
      .v301 = !digitalRead(pinout::MISSILE_SWITCH_2),
      .v405 = digitalRead(pinout::MISSILE_SWITCH_3),
>>>>>>> 4633435 (Initial E-Pump spin test RLCS config)
      .tank_heating_1 = digitalRead(pinout::MISSILE_SWITCH_8),
      .tank_heating_2 = digitalRead(pinout::MISSILE_SWITCH_8),
      .ignition_primary =
          digitalRead(pinout::MISSILE_SWITCH_IGNITION_PRI) &&
          !digitalRead(pinout::MISSILE_SWITCH_IGNITION_FIRE), // active low
      .ignition_secondary = // fire secondary ignition with primary ignition switch
        digitalRead(pinout::MISSILE_SWITCH_IGNITION_PRI) &&
        !digitalRead(pinout::MISSILE_SWITCH_IGNITION_FIRE), // active low
  };
}

} // namespace config
