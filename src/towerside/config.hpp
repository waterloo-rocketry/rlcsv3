#ifndef CONFIG_H
#define CONFIG_H

#include "actuators.hpp"
#include "sensors.hpp"
#include "common/config.hpp"

namespace Config {

extern const uint16_t SEND_STATUS_INTERVAL_MS;
extern const uint16_t TIME_TO_SAFE_STATE_S;
extern const uint16_t ACTUATOR_DISPATCH_INTERVAL_MS;

void setup();
Actuator::Actuator *get_actuator(ActuatorID::ActuatorID id);
Sensor::Sensor *get_sensor(SensorID::SensorID id);

const ActuatorCommand &get_default_states();
const ActuatorCommand &get_safe_states();

}

#endif
