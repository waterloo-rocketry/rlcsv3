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

; // random semicolon to fix clangd warning bug, see: https://stackoverflow.com/questions/72456118/why-does-clang-give-a-warning-unterminated-pragma-pack-push-at-end-of-f
#pragma pack(push, 1)
struct USBMessage {
  ActuatorMessage actuator_msg;
  SensorMessage sensor_msg;
};
#pragma pack(pop)

} // namespace config

#endif
