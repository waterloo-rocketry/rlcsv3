#include "config.hpp"
#include "common/mock_arduino.hpp"
#include "pinout.hpp"

namespace config {

ActuatorMessage build_command_message() {
  return ActuatorMessage {
    .valve_1 = digitalRead(pinout::MISSILE_SWITCH_1),
    .valve_2 = digitalRead(pinout::MISSILE_SWITCH_2),
    .valve_3 = digitalRead(pinout::MISSILE_SWITCH_3),
	.valve_4 = digitalRead(pinout::MISSILE_SWITCH_4),
    .injector_valve = digitalRead(pinout::MISSILE_SWITCH_INJECTOR),
    .ignition_primary = digitalRead(pinout::MISSILE_SWITCH_IGNITION_PRI) && \
                        !digitalRead(pinout::MISSILE_SWITCH_IGNITION_SEC) && \
                        !digitalRead(pinout::MISSILE_SWITCH_IGNITION_FIRE), // active low
    .ignition_secondary = digitalRead(pinout::MISSILE_SWITCH_IGNITION_SEC) && \
                          !digitalRead(pinout::MISSILE_SWITCH_IGNITION_PRI) && \
                          !digitalRead(pinout::MISSILE_SWITCH_IGNITION_FIRE), // active low
  };
}

} // namespace config
