#include "sensors.hpp"

#include "common/mock_arduino.hpp"
#include "pinout.hpp"

namespace sensors {

uint16_t get_main_batt_mv() {
  return analogRead(pinout::MAIN_BATT_VOLTAGE) * 48 / 17 * 5;
}

uint16_t get_actuator_batt_mv() {
  return analogRead(pinout::ACTUATOR_BATT_VOLTAGE) * 48 / 17 * 5;
}

uint16_t get_towerside_state() {
  return 0; // TODO
}

} // namespace sensors
