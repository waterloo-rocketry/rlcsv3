#include "sensors.hpp"

#include "common/mock_arduino.hpp"
#include "pinout.hpp"

namespace sensors {

uint16_t get_main_batt_mv() {
  return static_cast<uint16_t>(analogRead(pinout::MAIN_BATT_VOLTAGE)) * 48 / 17 * 5;
}

uint16_t get_actuator_batt_mv() {
  return static_cast<uint16_t>(analogRead(pinout::ACTUATOR_BATT_VOLTAGE)) * 48 / 17 * 5;
}

uint16_t get_towerside_state() {
  return 0; // TODO
}

} // namespace sensors
