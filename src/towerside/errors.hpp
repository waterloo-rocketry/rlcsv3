#ifndef ERRORS_H
#define ERRORS_H

#include <stdint.h>

namespace errors {

void push(uint8_t id, uint8_t code);
uint16_t pop();

} // namespace errors

#endif
