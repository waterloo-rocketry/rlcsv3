#ifndef RECEIVER_H
#define RECEIVER_H

#include <stdint.h>
#include "../tickable.hpp"
#include "decoder.hpp"
#include "connection.hpp"

namespace Communication {

template <typename T>
class MessageHandler {
  public:
    virtual void handle(const T &message) = 0;
};

// A MessageReceiver takes a Serializable class and a handler, which gets
// called whenever a complete message is recieved.
template <typename T>
class MessageReceiver: public Tickable {
  Decoder<T> &decoder;
  Connection &connection;
  uint8_t n;
  MessageHandler<T> **handlers;
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
      Serial.println((int)c);
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
};

}

#endif
