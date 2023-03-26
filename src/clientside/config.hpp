#ifndef CONFIG_H
#define CONFIG_H

#include "common/config.hpp"
#include <stdint.h>

namespace config {

ActuatorMessage build_command_message();

constexpr unsigned long COMMAND_MESSAGE_INTERVAL_MS = 100;
constexpr unsigned long COMMUNICATION_RESET_MS = 50;
constexpr uint16_t COMMUNICATION_TIMEOUT_S = 3;

constexpr uint16_t BATT_SCALE_PRE_OFFSET = -11;
constexpr uint16_t BATT_SCALE_NUM = 1;
constexpr uint16_t BATT_SCALE_DEN = 7;

} // namespace config

#endif
