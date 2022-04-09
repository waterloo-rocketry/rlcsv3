#ifndef CONFIG_H
#define CONFIG_H

#include "actuators.hpp"
#include "sensors.hpp"
#include "common/config.hpp"

namespace Config {

void setup();
Actuator *get_actuator(ActuatorID::ActuatorID id);
Sensor *get_sensor(SensorID::SensorID id);

ActuatorCommand get_default_states();
ActuatorCommand get_safe_states();

}

#endif
