#ifndef CONFIG_H
#define CONFIG_H

#include <stdint.h>

#include "common/config.hpp"

namespace config {

void apply(const ActuatorMessage &command);

ActuatorMessage build_safe_state(const ActuatorMessage &current_state);

SensorMessage build_sensor_message();

extern const uint8_t COMMUNICATION_TIMEOUT_S;
extern const uint8_t COMMUNICATION_RESET_MS;
extern const uint16_t SENSOR_MSG_INTERVAL_MS;

} // namespace config

#endif
