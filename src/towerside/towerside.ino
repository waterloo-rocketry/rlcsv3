#include "common/mock_arduino.hpp"
#include "common/connection.hpp"
#include "config.hpp"
#include "command_handler.hpp"

MessageProcessor<ActuatorCommand> *receiver;
ActuatorCommandHandler *handler;
void setup() {
  Config::setup();
  SerialConnection connection(Serial);
  auto handler = new ActuatorCommandHandler(Config::get_default_states());
  auto processor = new MessageProcessor<ActuatorCommand>(handler);

  while (true) {
    if (connection.char_available()) {
      processor->handle_char(connection.get_char());
    }
  }
}

void loop() {
}
