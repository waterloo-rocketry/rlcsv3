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
  return (analogRead(Pinout::BATT_VOLTAGE) + Config::BATT_SCALE_PRE_OFFSET) * Config::BATT_SCALE_NUM / Config::BATT_SCALE_DEN;
}

}
