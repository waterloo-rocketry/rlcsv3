#include "sensors.hpp"

#include "common/mock_arduino.hpp"
#include "pinout.hpp"

namespace sensors {

void setup() {
  pinMode(pinout::MAIN_BATT_VOLTAGE, INPUT);
  pinMode(pinout::ACTUATOR_BATT_VOLTAGE, INPUT);
  pinMode(pinout::KEY_SWITCH_IN, INPUT_PULLUP);
  pinMode(pinout::KEY_SWITCH_GND, OUTPUT); // the other side of the key switch is just a digital pin
  digitalWrite(pinout::KEY_SWITCH_GND, false);
}

bool is_armed() {
  // Key switch pin gets pulled down to GND when the key is removed, aka we are armed
  return !digitalRead(pinout::KEY_SWITCH_IN);
}

bool contact;
bool has_contact() {
  return contact;
}
void set_contact(bool value) {
  contact = value;
}

uint16_t get_main_batt_mv() {
  return static_cast<uint16_t>(analogRead(pinout::MAIN_BATT_VOLTAGE)) * 48 / 17 * 5;
}

uint16_t get_actuator_batt_mv() {
  return static_cast<uint16_t>(analogRead(pinout::ACTUATOR_BATT_VOLTAGE)) * 48 / 17 * 5;
}

uint16_t get_towerside_state() {
  return static_cast<uint8_t>(!has_contact()) << 0 | \
         static_cast<uint8_t>(!is_armed())    << 1;
}

} // namespace sensors
