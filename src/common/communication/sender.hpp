#ifndef SENDER_H
#define SENDER_H

#include <stdint.h>
#include "encoder.hpp"
#include "connection.hpp"

namespace Communication {

// Encode and send messages over a connection using the specified encoder.
template <typename T>
class MessageSender {
  uint8_t buf[T::DATA_LENGTH];
  Encoder<T> &encoder;
  Connection &connection;
  public:
    MessageSender(Encoder<T> &encoder, Connection &connection): encoder{encoder}, connection{connection} {}
    bool send(const T &message) {
      if (message.encode(buf)) {
        return encoder.send(buf, connection);
      }
      return false;
    }
};

}

#endif
