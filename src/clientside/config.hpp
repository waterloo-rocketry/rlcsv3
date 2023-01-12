#ifndef CONFIG_H
#define CONFIG_H

#include "common/config.hpp"
#include <stdint.h>

namespace config {

  ActuatorContainer<bool> build_command_message();

  extern const uint8_t COMMAND_MESSAGE_INTERVAL_MS;
  extern const uint8_t COMMUNICATION_RESET_MS;
  extern const uint8_t COMMUNICATION_TIMEOUT_S;

  constexpr uint16_t BATT_SCALE_PRE_OFFSET = -11;
  constexpr uint16_t BATT_SCALE_NUM = 1;
  constexpr uint16_t BATT_SCALE_DEN = 7;
} // namespace config

#endif
