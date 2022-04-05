#ifndef CONFIG_H
#define CONFIG_H

#include "actuators.hpp"
#include "sensors.hpp"
#include "common/config.hpp"

namespace TowerConfig {

void setup();
Actuator *get_actuator(ActuatorID::ActuatorID id);
Sensor *get_sensor(SensorID::SensorID id);

}

#endif
