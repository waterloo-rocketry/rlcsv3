#include "common/mock_arduino.hpp"
#include "config.hpp"

void setup() {
  TowerConfig::get_actuator(ActuatorID::fill_valve);
  TowerConfig::setup();
}

void loop() {
  //process_serial_bytes();
}
