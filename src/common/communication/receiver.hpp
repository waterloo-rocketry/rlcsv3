#ifndef RECEIVER_H
#define RECEIVER_H

#include <stdint.h>
#include "../tickable.hpp"
#include "decoder.hpp"
#include "connection.hpp"

namespace Communication {

// MessageHandlers get registered with a MessageReceiver to get callbacks when a message is received.
template <typename T>
class MessageHandler {
  public:
    virtual void handle(const T &message) = 0;
};

// A MessageReceiver handles interfacing a Connection and a Decoder, and calling out to a set of Handlers to handle the message.
template <typename T>
class MessageReceiver: public Tickable {
  Decoder<T> &decoder;
  Connection &connection;
  uint8_t n;
  MessageHandler<T> **handlers; // Array of MessageHandler pointers
  public:
    // To let us take a variable number of args we use a templated constructor.
    // Actual typechecking is enforced by the fact that we shove the arguments directly into a MessageHandler<T> array.
    template <typename... Handlers>
    MessageReceiver(Decoder<T> &decoder, Connection &connection, Handlers... hs):
      decoder{decoder}, connection{connection},
      n{sizeof...(hs)}, // Set n to the number of arguments
      handlers{new MessageHandler<T>*[n] {hs...}} {} // Allocate handers on the heap, initialized with the args
    void tick() override {
      if (!connection.char_available()) {
        return;
      }
      char c = connection.get_char();
      decoder.push_char(c);
      if (decoder.message_available()) {
        T t;
        if (t.decode(decoder.get_data())) {
          for (uint8_t i = 0; i < n; i++) {
            handlers[i]->handle(t);
          }
        }
      }
    }
    // Force the handlers to handle a specific message (eg when transitioning to safe state)
    void force(const T &msg) {
      for (uint8_t i = 0; i < n; i++) {
        handlers[i]->handle(msg);
      }
    }
};

}

#endif
