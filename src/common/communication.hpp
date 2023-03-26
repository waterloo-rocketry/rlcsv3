#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include "mock_arduino.hpp"
#include <stdint.h>

template <typename ST, typename RT> class Communicator {
  Stream &stream;
  static const size_t BUFF_SIZE = sizeof(RT) + 2;
  uint8_t receive_buffer[BUFF_SIZE];

  size_t buffer_position = 0;
  unsigned long time_of_last_byte = 0;
  const unsigned long reset_interval_ms;

public:
  Communicator(Stream &stream, unsigned long reset_interval_ms)
      : stream{stream}, reset_interval_ms{reset_interval_ms} {}

  void send(const ST &send_data) {
    const uint8_t *send_data_uint8 =
        reinterpret_cast<const uint8_t *>(&send_data);

    stream.write('W');
    stream.write(send_data_uint8, sizeof(ST));
    stream.write('R');
    stream.write('\n');
  }

  bool get_message(RT *dest) {
    if (buffer_position < BUFF_SIZE) {
      return false;
    }

    if (receive_buffer[0] != 'W' || receive_buffer[sizeof(RT) + 1] != 'R') {
      buffer_position = 0;
      return false;
    }

    memcpy(dest, receive_buffer + 1, sizeof(RT));
    buffer_position = 0;
    return true;
  }

  uint16_t seconds_since_last_contact() {
    return (millis() - time_of_last_byte) / 1000;
  }

  bool read_byte() {
    if (stream.available()) {
      if (buffer_position < BUFF_SIZE) {
        receive_buffer[buffer_position++] = static_cast<uint8_t>(stream.read());
      }
      time_of_last_byte = millis();
      return true;
    }
    if (millis() - time_of_last_byte > reset_interval_ms) {
      buffer_position = 0;
    }

    return false;
  }
};

#endif
