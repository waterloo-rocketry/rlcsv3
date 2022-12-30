#include "errors.hpp"

namespace errors {

#define BUF_SIZE 10
uint16_t errors[BUF_SIZE]; // ringbuffer of errors
uint8_t err_index = 0; // index of oldest error stored
uint8_t err_len = 0; // number of stored errors
// In order to make sure we show all the errors we see,
// if the buffer overflows we completely drain it before
// allowing new errors to be added.
bool full = false; // whether we are draining the buffer

void push(uint8_t id, uint8_t code) {
  if (full) {
    return;
  }
  errors[(err_index + err_len) % BUF_SIZE] = (static_cast<uint16_t>(id) << 8) | code;
  err_len++;
  if (err_len == BUF_SIZE) {
    full = true;
  }
}

uint16_t pop() {
  if (err_len == 0) {
    return 0;
  }
  uint16_t res = errors[err_index];
  err_index = (err_index + 1) % BUF_SIZE;
  err_len--;
  if (err_len == 0) {
    full = false;
  }
  return res;
}

} // namespace errors
