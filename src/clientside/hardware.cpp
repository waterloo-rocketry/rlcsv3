#include "hardware.hpp"
#include "common/mock_arduino.hpp"
#include "pinout.hpp"

namespace Hardware {

// Do any hardware-specific setup that doesn't have a good place elsewhere.
void setup() {
  //Serial.begin(115200); // Computer connection
  Serial3.begin(9600); // XBee connection
  Wire.begin();
  Wire.setWireTimeout(1000, true); // 1000uS = 1mS timeout, true = reset the bus in this case.

  // This code is structured badly and so we just set up the key switch and missile LEDs here.
  pinMode(Pinout::KEY_SWITCH_IN, INPUT_PULLUP);
  pinMode(Pinout::KEY_SWITCH_GND, OUTPUT); // the "ground" of the key switch is just another digital pin.
  digitalWrite(Pinout::KEY_SWITCH_GND, false);

  pinMode(Pinout::LED_RED, OUTPUT);
  pinMode(Pinout::LED_GREEN, OUTPUT);
  pinMode(Pinout::LED_BLUE, OUTPUT);

  for (uint8_t i = 0; i < sizeof(Pinout::MISSILE_LEDS) / sizeof(Pinout::MISSILE_LEDS[0]); i++) {
    pinMode(Pinout::MISSILE_LEDS[i], OUTPUT);
  }
}

}
