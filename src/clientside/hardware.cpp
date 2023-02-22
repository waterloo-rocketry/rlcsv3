#include "hardware.hpp"
#include "common/mock_arduino.hpp"

#include "config.hpp"
#include "pinout.hpp"

namespace hardware {

void setup() {
  pinMode(pinout::KEY_SWITCH_IN, INPUT_PULLUP);
  pinMode(pinout::KEY_SWITCH_GND, OUTPUT);
  digitalWrite(pinout::KEY_SWITCH_GND, false);

  pinMode(pinout::MISSILE_SWITCH_IGNITION_FIRE, INPUT_PULLUP);

  for (unsigned int i = 0; i < (sizeof(pinout::MISSILE_LEDS) / sizeof(pinout::MISSILE_LEDS[0])); i++) {
    pinMode(pinout::MISSILE_LEDS[i], OUTPUT);
  }

  pinMode(pinout::LED_RED, OUTPUT);
  pinMode(pinout::LED_GREEN, OUTPUT);
  pinMode(pinout::LED_BLUE, OUTPUT);
}

void set_missile_leds(bool value) {
  for (unsigned int i = 0; i < (sizeof(pinout::MISSILE_LEDS) / sizeof(pinout::MISSILE_LEDS[0])); i++) {
    digitalWrite(pinout::MISSILE_LEDS[i], !value); // Active low
  }
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
