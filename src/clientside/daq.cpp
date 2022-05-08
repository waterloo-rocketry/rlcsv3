#include "daq.hpp"
#include "config.hpp"
#include "pinout.hpp"

namespace DAQ {

// Actually go through and read the missile switches to build up an ActuatorCommand
ActuatorCommand get_switch_positions () {
  ActuatorCommand msg;
  for (uint8_t i = 0; i < NUM_ACTUATORS; i++) {
    ActuatorID::ActuatorID id = static_cast<ActuatorID::ActuatorID>(i);
    msg.set_actuator(id, Config::get_switch(id)->is_pressed());
  }
  return msg;
}

// get clientside battery voltage in 10ths of a volt for displaying
uint8_t get_batt_dv() {
  // 6.2k and 10k resistor divider plus arduino's analog read being on a scale of 2^10 = 5V gives these magic scaling numbers
  return analogRead(Pinout::BATT_VOLTAGE) * 4 / 31;
}

}
