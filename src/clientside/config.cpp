#include "config.hpp"
#include "common/mock_arduino.hpp"
#include "pinout.hpp"

namespace config {

ActuatorMessage build_command_message() {
  return ActuatorMessage{
      .NV102 = digitalRead(pinout::MISSILE_SWITCH_2),
      .NV103 = digitalRead(pinout::MISSILE_SWITCH_6),
      .NV104 = digitalRead(pinout::MISSILE_SWITCH_5),
      .NV105 = digitalRead(pinout::MISSILE_SWITCH_1),
      .OV102 = digitalRead(pinout::MISSILE_SWITCH_7),
      .FV102 = digitalRead(pinout::MISSILE_SWITCH_8),
      .OV101v = digitalRead(pinout::MISSILE_SWITCH_3),
      .FV101v = digitalRead(pinout::MISSILE_SWITCH_4),
      .automatic_mode = digitalRead(pinout::MISSILE_SWITCH_INJECTOR),
      .sequence_a = digitalRead(pinout::MISSILE_SWITCH_IGNITION_PRI),
      .sequence_b = digitalRead(pinout::MISSILE_SWITCH_IGNITION_SEC),
      .start_sequence = !digitalRead(pinout::MISSILE_SWITCH_IGNITION_FIRE),
      .ignition = false
  };
}

} // namespace config
