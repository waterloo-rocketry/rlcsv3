#ifndef DECODER_H
#define DECODER_H

#include <stdint.h>

namespace Communication {

// A decoder takes a Serializable type T that provides T::DATA_LENGTH, and tries to listen
// to a stream of characters for a message of that length.
template <typename T>
class Decoder {
  public:
    virtual void push_char(char c) = 0; // Give the decoder a new character
    virtual const uint8_t *get_data() = 0; // Get a pointer to an array of length T::DATA_LENGTH holding the decoded message
    virtual bool message_available() = 0; // Check if a complete message has been received
};

// A HexDecoder gets templated by the length of message to look for
// (so that it can initialize its buffer on the stack). It then scans
// for that many hex byte enclosed in the message guards 'W' and 'R'.
// (so full messages take the form W<hex>R).
template <typename T>
class HexDecoder: public Decoder<T> {
  uint8_t buf[T::DATA_LENGTH];
  bool message_in_progress = false; // if we are currently decoding a message
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
    HexDecoder() {}
    void push_char(char c) {
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
      if (i == T::DATA_LENGTH * 2) {
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
      // don't report the same message more than once, clear message_available once it's been receieved
      message_in_progress = false;
      i = 0;
      return buf;
    }
    bool message_available() {
      return i == T::DATA_LENGTH * 2 && !message_in_progress;
    }
};


}

#endif
