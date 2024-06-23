#include "config.hpp"
#include "common/mock_arduino.hpp"
#include "pinout.hpp"

namespace config {

ActuatorMessage build_command_message() {
  return ActuatorMessage{
      .ov101 = digitalRead(pinout::MISSILE_SWITCH_1),
      .ov102 = digitalRead(pinout::MISSILE_SWITCH_2),
      .nv101 = digitalRead(pinout::MISSILE_SWITCH_3),
      .nv102 = digitalRead(pinout::MISSILE_SWITCH_4),
      .fill_disconnect = digitalRead(pinout::MISSILE_SWITCH_5),
	  .rocket_power = digitalRead(pinout::MISSILE_SWITCH_8),
      .ignition_primary =
          digitalRead(pinout::MISSILE_SWITCH_IGNITION_PRI) &&
          !digitalRead(pinout::MISSILE_SWITCH_IGNITION_SEC) &&
          !digitalRead(pinout::MISSILE_SWITCH_IGNITION_FIRE), // active low
      .ignition_secondary =
          digitalRead(pinout::MISSILE_SWITCH_IGNITION_SEC) &&
          !digitalRead(pinout::MISSILE_SWITCH_IGNITION_PRI) &&
          !digitalRead(pinout::MISSILE_SWITCH_IGNITION_FIRE), // active low
  };
}

} // namespace config
