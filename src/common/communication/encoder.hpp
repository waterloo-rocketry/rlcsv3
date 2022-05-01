#ifndef ENCODER_H
#define ENCODER_H

#include <stdint.h>
#include "connection.hpp"

namespace Communication {

template <typename T>
class Encoder {
  public:
    virtual bool send(const uint8_t (&data)[T::DATA_LENGTH], Connection &connection) = 0;
};

template <typename T>
class HexEncoder: public Encoder<T> {
  char get_nibble(uint8_t val) {
    if (val < 10) {
      return '0' + val;
    } else if (val < 16) {
      return 'A' + val - 10;
    } else {
      return 'G';
    }
  }
  public:
    bool send(const uint8_t (&data)[T::DATA_LENGTH], Connection &connection) override {
      bool success = true;
      success &= connection.push_char('W');
      for (uint8_t i = 0; i < T::DATA_LENGTH; i++) {
        success &= connection.push_char(get_nibble(data[i] >> 4));
        success &= connection.push_char(get_nibble(data[i] & 0xF));
      }
      success &= connection.push_char('R');
      success &= connection.push_char('\n');
      return success;
    }
};

}

#endif
