#ifndef CONFIG_H
#define CONFIG_H

#include <stdint.h>

#include "common/config.hpp"

namespace config {

void apply(const ActuatorMessage &command);
ActuatorMessage build_safe_state(const ActuatorMessage &current_state);
SensorMessage build_sensor_message();

constexpr uint8_t COMMUNICATION_TIMEOUT_S = 10; // Go to safe state after this many seconds without contact
constexpr unsigned long SENSOR_MSG_INTERVAL_MS = 100; // Rate to send sensor messages at
constexpr unsigned long COMMUNICATION_RESET_MS = 50; // maximum time between successive characters in the same message

} // namespace config

#endif
