#include "common/mock_arduino.hpp"
#include "common/connection.hpp"
#include "config.hpp"
#include "command_handler.hpp"

void setup() {
  Config::setup();
  SerialConnection connection(Serial);
  auto handler = new ActuatorCommandHandler(Config::get_default_states());
  auto receiver = new MessageReceiver<ActuatorCommand>{handler, handler};

  while (true) {
    if (connection.char_available()) {
      char c = connection.get_char();
      receiver->handle_char(c);
    }
  }
}

void loop() {
}
