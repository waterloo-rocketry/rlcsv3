#ifndef ERRORS_H
#define ERRORS_H

#include <cstdint>

namespace errors {

void push(uint8_t id, uint8_t code);
uint16_t pop();

enum ErrorCode: uint16_t {
  I2CWriteError,
  I2CReadError,
};

} // namespace errors

#endif
