#include "daq.hpp"
#include "config.hpp"

namespace DAQ {

ActuatorCommand get_switch_positions () {
  ActuatorCommand msg;
  for (uint8_t i = 0; i < NUM_ACTUATORS; i++) {
    ActuatorID::ActuatorID id = static_cast<ActuatorID::ActuatorID>(i);
    msg.set_actuator(id, Config::get_switch(id)->is_pressed());
  }
  return msg;
}

}
