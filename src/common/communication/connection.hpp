#ifndef CONNECTION_H
#define CONNECTION_H

#include <stdint.h>
#include "../mock_arduino.hpp"

namespace Communication {

class Connection {
  unsigned long last_recv_timestamp = 0;
  public:
    virtual bool char_available() = 0;
    char get_char() {
      char c = _get_char();
      last_recv_timestamp = millis();
      return c;
    }
    bool push_char(char c) { // wrapper for symmetry
      return _push_char(c);
    }
    uint16_t seconds_since_contact() {
      if (last_recv_timestamp > 65535*1000) {
        return 65535;
      }
      return (millis() - last_recv_timestamp) / 1000;
    }
  private:
    virtual char _get_char() = 0;
    virtual bool _push_char(char c) = 0;
};

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
