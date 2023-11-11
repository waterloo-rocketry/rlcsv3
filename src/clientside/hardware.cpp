#include "hardware.hpp"
#include "common/mock_arduino.hpp"

#include "config.hpp"
#include "pinout.hpp"

namespace hardware {

void setup() {
  pinMode(pinout::KEY_SWITCH_IN, INPUT_PULLUP);

  pinMode(pinout::MISSILE_SWITCH_IGNITION_FIRE, INPUT_PULLUP);

  pinMode(pinout::MISSILE_LED, OUTPUT);

  pinMode(pinout::LED_RED, OUTPUT);
  pinMode(pinout::LED_GREEN, OUTPUT);
  pinMode(pinout::LED_BLUE, OUTPUT);
}

void set_missile_leds(bool value) {
  digitalWrite(pinout::MISSILE_LED, value); // Active high
}

void set_status_startup() {
  digitalWrite(pinout::LED_RED, false);
  digitalWrite(pinout::LED_GREEN, false);
  digitalWrite(pinout::LED_BLUE, true);
}

void set_status_connected() {
  digitalWrite(pinout::LED_RED, false);
  digitalWrite(pinout::LED_GREEN, true);
  digitalWrite(pinout::LED_BLUE, false);
}

void set_status_disconnected() {
  digitalWrite(pinout::LED_RED, true);
  digitalWrite(pinout::LED_GREEN, false);
  digitalWrite(pinout::LED_BLUE, false);
}

bool is_armed() {
  // Key switch pin gets pulled down to ground when the switch is active
  return !digitalRead(pinout::KEY_SWITCH_IN);
}

uint8_t get_batt_dv() {
  return (analogRead(pinout::BATT_VOLTAGE) + config::BATT_SCALE_PRE_OFFSET) *
         config::BATT_SCALE_NUM / config::BATT_SCALE_DEN;
}

} // namespace hardware
