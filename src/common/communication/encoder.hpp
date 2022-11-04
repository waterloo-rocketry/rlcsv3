#ifndef ENCODER_H
#define ENCODER_H

#include <stdint.h>
#include "connection.hpp"
#include "can.hpp"

namespace Communication {

// Encode a data array of length T::DATA_LENGTH and send it over a Connection
template <typename T>
class Encoder {
  public:
    // Pass the connection rather than using another buffer to output in to save space
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
      success &= connection.push_char('\n'); // technically not necessary but makes things readable by humans.
      return success;
    }
};

class CANEncoder: public Encoder<CANMessage> {
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
    bool send(const uint8_t (&data)[CANMessage::DATA_LENGTH], Connection &connection) override {
      bool success = true;
      uint8_t sum1 = 0;
      uint8_t sum2 = 0;
      success &= connection.push_char('m');
      success &= connection.push_char(get_nibble(data[0] & 0xF));
      sum1 = (sum1 + (data[0] & 0xf)) % 15;
      sum2 = (sum1 + sum2) % 15;
      success &= connection.push_char(get_nibble(data[1] >> 4));
      sum1 = (sum1 + (data[1] >> 4)) % 15;
      sum2 = (sum1 + sum2) % 15;
      success &= connection.push_char(get_nibble(data[1] & 0xF));
      sum1 = (sum1 + (data[1] & 0xf)) % 15;
      sum2 = (sum1 + sum2) % 15;
      for (uint8_t i = 0; i < 8; i++) {
        success &= connection.push_char(',');
        success &= connection.push_char(get_nibble(data[i + 2] >> 4));
        sum1 = (sum1 + (data[i + 2] >> 4)) % 15;
        sum2 = (sum1 + sum2) % 15;
        success &= connection.push_char(get_nibble(data[i + 2] & 0xF));
        sum1 = (sum1 + (data[i + 2] & 0xF)) % 15;
        sum2 = (sum1 + sum2) % 15;
      }
      success &= connection.push_char(';');
      success &= connection.push_char(get_nibble(sum1 ^ sum2));
      success &= connection.push_char('\r'); // technically not necessary but makes things readable by humans.
      success &= connection.push_char('\n'); // technically not necessary but makes things readable by humans.

      return success;
    }

};

}

#endif
