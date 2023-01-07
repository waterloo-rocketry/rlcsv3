#ifndef CONFIG_H
#define CONFIG_H

#include <stdint.h>
#include "common/config.hpp"

namespace config {

ActuatorContainer<bool> build_command_message();

extern const uint8_t COMMAND_MESSAGE_INTERVAL_MS;
extern const uint8_t COMMUNICATION_RESET_MS;
extern const uint8_t COMMUNICATION_TIMEOUT_S;

} // namespace config

#endif
