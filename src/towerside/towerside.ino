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
  Hardware::setup();
  Config::setup();
  auto connection = Communication::SerialConnection(Serial);
  auto actuators_handler = CommandHandler::Actuators(Config::get_default_states(), Pinout::KEY_SWITCH_IN, Pinout::KEY_SWITCH_GND);
  auto seven_seg_handler = CommandHandler::SevenSeg(Config::get_default_states());
  auto encoder = Communication::HexEncoder<SensorData>();
  auto decoder = Communication::HexDecoder<ActuatorCommand>();
  auto receiver = Communication::MessageReceiver<ActuatorCommand>(decoder, connection,
                                                                  &actuators_handler,
                                                                  &seven_seg_handler);
  auto sender = Communication::MessageSender<SensorData>(encoder, connection);

  unsigned long last_message_sent = 0;
  while (true) {
    Tickable::trigger_tick();
    if (connection.seconds_since_contact() >= Config::TIME_TO_SAFE_STATE) {
      actuators_handler.apply(Config::get_safe_states());
      seven_seg_handler.set_contact(false);
    } else {
      seven_seg_handler.set_contact(true);
    }
    if (millis() - last_message_sent > Config::SEND_STATUS_INTERVAL_MS) {
      last_message_sent = millis();

      sender.send(DAQ::get_sensor_message());
    }
  }
}

void loop() {
}
