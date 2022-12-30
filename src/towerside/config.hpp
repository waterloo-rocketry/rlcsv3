#ifndef CONFIG_H
#define CONFIG_H

#include <cstdint>

#include "common/config.hpp"

namespace config {

void apply(const ActuatorContainer<bool> &command);

void apply_safe_state();

SensorContainer<uint16_t> build_sensor_message();

extern const uint8_t COMMUNICATION_TIMEOUT_S;
extern const uint16_t SENSOR_MSG_INTERVAL_MS;

} // namespace config

#endif
