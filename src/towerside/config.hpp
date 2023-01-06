#ifndef CONFIG_H
#define CONFIG_H

#include <stdint.h>

#include "common/config.hpp"

namespace config {

void apply(const ActuatorContainer<bool> &command);

void apply_safe_state();

SensorContainer<uint16_t> build_sensor_message();

extern const uint8_t COMMUNICATION_TIMEOUT_S;
extern const uint8_t COMMUNICATION_RESET_MS;
extern const uint16_t SENSOR_MSG_INTERVAL_MS;

} // namespace config

#endif
