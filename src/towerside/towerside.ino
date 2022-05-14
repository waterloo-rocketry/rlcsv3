#include "common/mock_arduino.hpp"
#include "common/communication/receiver.hpp"
#include "common/communication/sender.hpp"
#include "common/tickable.hpp"
#include "config.hpp"
#include "command_handler.hpp"
#include "daq.hpp"
#include "hardware.hpp"
#include "pinout.hpp"

void setup() {
  // Set up hardware
  Hardware::setup();
  // Initialize configuration arrays (actuators, sensors, default + safe states)
  Config::setup();
  // Connect to client side of the Serial port
  auto connection = Communication::SerialConnection(Serial2);
  // Define handles for commands from client side
  auto actuators_handler = CommandHandler::Actuators(Config::get_default_states(), Pinout::KEY_SWITCH_IN, Pinout::KEY_SWITCH_GND);
  auto seven_seg_handler = CommandHandler::SevenSeg(Config::get_default_states(), Pinout::KEY_SWITCH_IN); // TODO: Make a generic arming class to pass around
  // Define how we will encode and decode messages to/from clientside
  auto encoder = Communication::HexEncoder<SensorData>();
  auto decoder = Communication::HexDecoder<ActuatorCommand>();
  auto receiver = Communication::MessageReceiver<ActuatorCommand>(decoder, connection,
                                                                  &actuators_handler,
                                                                  &seven_seg_handler);
  auto sender = Communication::MessageSender<SensorData>(encoder, connection);

  unsigned long last_message_sent = 0;
  while (true) {
    // Call the tick() methods on anything that inherits from Tickable
    Tickable::trigger_tick();
    // If we haven't heard from client side in a while
    if (connection.seconds_since_contact() >= Config::TIME_TO_SAFE_STATE_S) {
      // Go to safe states
      receiver.force(Config::get_safe_states());
      // Show that we can't contact client side on the 7-segment
      seven_seg_handler.set_contact(false);
    } else {
      // Show our connection to client side is fine on the 7-segment
      seven_seg_handler.set_contact(true);
    }
    // If we need to send our status (actuator states, currents, DAQ data) to client side
    if (millis() - last_message_sent > Config::SEND_STATUS_INTERVAL_MS) {
      last_message_sent = millis();
      // Send stuff along
      sender.send(DAQ::get_sensor_message());
    }
  }
}

void loop() {
}
