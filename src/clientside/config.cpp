#include "config.hpp"
#include "common/mock_arduino.hpp"
#include "pinout.hpp"

namespace config {

ActuatorMessage build_command_message() {
  return ActuatorMessage{
      .ov101 = digitalRead(pinout::MISSILE_SWITCH_1),
      .ov102 = digitalRead(pinout::MISSILE_SWITCH_2),
      .ov103 = digitalRead(pinout::MISSILE_SWITCH_6),
      .injector_valve = digitalRead(pinout::MISSILE_SWITCH_INJECTOR),
      .tank_heating_1 = digitalRead(pinout::MISSILE_SWITCH_8),
      .tank_heating_2 = digitalRead(pinout::MISSILE_SWITCH_8),
      .ignition_primary = digitalRead(pinout::MISSILE_SWITCH_IGNITION_PRI)
      .ignition_secondary = digitalRead(pinout::MISSILE_SWITCH_IGNITION_SEC)
      .ignition_fire = digitalRead(pinout::MISSILE_SWITCH_IGNITION_FIRE)
  };
}

} // namespace config
