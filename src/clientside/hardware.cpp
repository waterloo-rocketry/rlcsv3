#include "hardware.hpp"
#include "common/mock_arduino.hpp"
#include "pinout.hpp"

namespace Hardware {

void setup() {
  Serial.begin(115200);
  Wire.begin();
  Wire.setWireTimeout(1000, true); // 1000uS = 1mS timeout, true = reset the bus in this case.

  pinMode(Pinout::KEY_SWITCH_IN, INPUT_PULLUP);
  pinMode(Pinout::KEY_SWITCH_GND, OUTPUT);
  digitalWrite(Pinout::KEY_SWITCH_GND, false);

  for (uint8_t i = 0; i < sizeof(Pinout::MISSILE_LEDS) / sizeof(Pinout::MISSILE_LEDS[0]); i++) {
    pinMode(Pinout::MISSILE_LEDS[i], OUTPUT);
  }
}

}
