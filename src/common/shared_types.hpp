#ifndef SHARED_TYPES_H
#define SHARED_TYPES_H

#include <stdint.h>
#include "config.hpp"

namespace ActuatorPosition {
enum ActuatorPosition : uint16_t {
  // Ordered this way so that position = open_lim + 2 * close_lim
  unknown = 0,
  open = 1,
  closed = 2,
  error = 3
};
} // namespace ActuatorPosition

// Put this value in a sensor data field to signify an error.
const uint16_t SENSOR_ERR_VAL = 0xFFFF;

#endif
