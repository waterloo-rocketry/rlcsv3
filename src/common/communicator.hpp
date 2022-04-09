#ifndef COMMUNICATOR_H
#define COMMUNICATOR_H

#include <stdint.h>
#include "debug.hpp"

class Serializable {
  public:
    static const uint8_t DATA_LENGTH;
    virtual bool encode(uint8_t *buf) = 0;
    virtual bool decode(const uint8_t *buf) = 0;
};

// A HexReciever gets templated by the length of message to look for
// (so that it can initialize its buffer on the stack). It then scans
// for that many hex byte enclosed in the message guards 'W' and 'R'.
// (so full messages take the form W<hex>R).
template <uint8_t MESSAGE_SIZE>
class HexReciever {
  uint8_t buf[MESSAGE_SIZE];
  bool message_in_progress = false;
  uint8_t i = 0; // index of the next nibble to decode
  bool valid_hex_char(char c) {
    return (c >= '0' && c <= '9') || (c >= 'A' && c <= 'F');
  }
  uint8_t get_nibble(char c) {
    if (c >= '0' && c <= '9') {
      return c - '0';
    } else if (c >= 'A' && c <= 'F') {
      return 10 + c - 'A';
    } else {
      return 0;
    }
  }
  public:
    HexReciever() {}
    void push_char(char c) {
      // DEBUG(message_in_progress << " " << (int)i << " " << c << " " << (int)(buf[0]));
      if (c == 'W') {
        // start of a new message, drop everything and follow it
        i = 0;
        message_in_progress = true;
        return;
      }
      if (!message_in_progress) {
        // no ongoing message and not a 'W', ignore.
        return;
      }
      if (i == MESSAGE_SIZE * 2) {
        // Should be the end of a message
        if (c == 'R') {
          // message complete!
          message_in_progress = false;
        } else {
          // message too long, drop it
          i = 0;
          message_in_progress = false;
        }
        return;
      }
      if (!valid_hex_char(c)) {
        // invalid byte, drop anything we have
        i = 0;
        message_in_progress = false;
        return;
      }
      if (i % 2 == 0) {
        buf[i / 2] = get_nibble(c) << 4;
      } else {
        buf[i / 2] |= get_nibble(c);
      }
      i++;
    }
    const uint8_t *get_data() {
      message_in_progress = false;
      i = 0;
      return buf;
    }
    bool message_available() {
      return i == MESSAGE_SIZE * 2 && !message_in_progress;
    }
};

template <typename T>
class MessageHandler {
  public:
    virtual void handle(T message) = 0;
};

// A MessageProcessor takes a Serializable class and a handler, which gets
// called whenever a complete message is recieved.
template <typename T>
class MessageProcessor {
  HexReciever<T::DATA_LENGTH> receiver;
  MessageHandler<T> *handler;
  public:
    MessageProcessor(MessageHandler<T> *handler): handler{handler} {}
    void handle_char(char c) {
      receiver.push_char(c);
      if (receiver.message_available()) {
        T t;
        if (t.decode(receiver.get_data())) {
          handler->handle(t);
        }
      }
    }
};

#endif
