#include "config.hpp"
#include "common/mock_arduino.hpp"
#include "pinout.hpp"

namespace config {

ActuatorContainer<bool> build_command_message() {
  return ActuatorContainer<bool> {
    .valve_1 = digitalRead(pinout::MISSILE_SWITCH_1),
    .valve_2 = digitalRead(pinout::MISSILE_SWITCH_2),
    .valve_3 = digitalRead(pinout::MISSILE_SWITCH_3),
    .injector_valve = digitalRead(pinout::MISSILE_SWITCH_INJECTOR),
    .ignition_primary = digitalRead(pinout::MISSILE_SWITCH_IGNITION_PRI) && \
                        !digitalRead(pinout::MISSILE_SWITCH_IGNITION_SEC) && \
                        !digitalRead(pinout::MISSILE_SWITCH_IGNITION_FIRE), // active low
    .ignition_secondary = digitalRead(pinout::MISSILE_SWITCH_IGNITION_SEC) && \
                          !digitalRead(pinout::MISSILE_SWITCH_IGNITION_PRI) && \
                          !digitalRead(pinout::MISSILE_SWITCH_IGNITION_FIRE), // active low
  };
}

const uint8_t COMMUNICATION_RESET_MS = 50;
const uint8_t COMMUNICATION_TIMEOUT_S = 3;
const uint8_t COMMAND_MESSAGE_INTERVAL_MS = 100;

} // namespace config
