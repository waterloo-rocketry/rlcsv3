#include "common/mock_arduino.hpp"
#include "common/communication/receiver.hpp"
#include "common/communication/sender.hpp"
#include "common/tickable.hpp"
#include "config.hpp"
#include "command_handler.hpp"
#include "daq.hpp"
#include "hardware.hpp"
#include "pinout.hpp"
#include "telemetry.hpp"

void setup() {
  // Set up hardware
  Hardware::setup();
  // Initialize configuration arrays (actuators, sensors, default + safe states)
  Config::setup();
  // Connect to client side of the Serial port
  Serial.println("I'm alive");
  auto connection = Communication::SerialConnection(Serial); // 2
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

  auto canConnection = Communication::SerialConnection(Serial3);
  auto canEncoder = Communication::CANEncoder();
  auto canSender = Communication::MessageSender<Communication::CANMessage>(canEncoder, canConnection);
  auto canDecoder = Communication::CANDecoder();
  auto canVentListener = static_cast<Telemetry::ActuatorStateListener*>(Config::get_sensor(SensorID::valve_3_state));
  auto canInjectorListener = static_cast<Telemetry::ActuatorStateListener*>(Config::get_sensor(SensorID::injector_valve_state));
  auto canReceiver = Communication::MessageReceiver<Communication::CANMessage>(canDecoder, canConnection,
                                                                               canVentListener,
                                                                               canInjectorListener);

  unsigned long last_message_sent = 0;
  unsigned long last_can_message_dispatch = 0;
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
    if (millis() - last_can_message_dispatch > Config::CAN_DISPATCH_INTERVAL_MS) {
      last_can_message_dispatch = millis();

      const Communication::CANMessage *msg;
      msg = static_cast<Actuator::RocketRadio*>(Config::get_actuator(ActuatorID::valve_3))->build_message();
      if (msg != nullptr) { canSender.send(*msg); }
      msg = static_cast<Actuator::RocketRadio*>(Config::get_actuator(ActuatorID::injector_valve))->build_message();
      if (msg != nullptr) { canSender.send(*msg); }
      msg = static_cast<Actuator::RocketRadio*>(Config::get_actuator(ActuatorID::remote_arming))->build_message();
      if (msg != nullptr) { canSender.send(*msg); }
      msg = static_cast<Actuator::RocketRadio*>(Config::get_actuator(ActuatorID::remote_disarming))->build_message();
      if (msg != nullptr) { canSender.send(*msg); }
    }
  }
}

void loop() {
}
