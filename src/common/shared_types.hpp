#ifndef SHARED_TYPES_H
#define SHARED_TYPES_H

#include <stdint.h>

namespace ActuatorPosition {
enum ActuatorPosition : uint8_t {
  // Ordered this way so that position = open_lim + 2 * close_lim
  unknown = 0,
  open = 1,
  closed = 2,
  error = 3
};
} // namespace ActuatorPosition

namespace ErrorCode {
enum ErrorCode: uint8_t {
  I2CWriteError,
  I2CReadError,
};
} // namespace ErrorCode

namespace sequence {
enum State {
    MANUAL,
    AUTOMATIC,
    SEQUENCE1,
    SEQUENCE2,
};
}

// Put this value in a sensor data field to signify an error.
const uint16_t SENSOR_ERR_VAL = 0xFFFF;

#endif
