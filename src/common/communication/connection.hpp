#ifndef CONNECTION_H
#define CONNECTION_H

#include <stdint.h>
#include "../mock_arduino.hpp"

namespace Communication {

// Wrap a generic connection that lets characters to be sent/receiver.
// Also keeps track of how long it's been since we heard from the other side.
class Connection {
  unsigned long last_recv_timestamp = 0;
  public:
    virtual bool char_available() = 0;
    char get_char() {
      char c = _get_char();
      last_recv_timestamp = millis();
      Serial.write(c);
      return c;
    }
    bool push_char(char c) { // wrapper for symmetry
      return _push_char(c);
    }
    uint16_t seconds_since_contact() {
      unsigned long delta = (millis() - last_recv_timestamp) / 1000;
      if (delta > 65535) {
        return 65535;
      }
      return delta;
    }
  private:
    // to be overridden by subclasses
    virtual char _get_char() = 0;
    virtual bool _push_char(char c) = 0;
};

// Connection that uses an arduino Serial interface (or technically a Stream).
class SerialConnection: public Connection {
  Stream &stream;
  public:
    SerialConnection(Stream &stream): stream{stream} {}
    bool char_available() override {
      return stream.available();
    }
    char _get_char() override {
      return stream.read();
    }
    bool _push_char(char c) override {
      return stream.write(c);
    }
};

}

#endif
