#include "common/mock_arduino.hpp"
#include "common/communication/receiver.hpp"
#include "common/communication/sender.hpp"
#include "common/tickable.hpp"
#include "config.hpp"
#include "data_handlers.hpp"
#include "daq.hpp"
#include "hardware.hpp"
#include "pinout.hpp"

void setup() {
  Hardware::setup();
  // blue LED to show we are starting up
  digitalWrite(Pinout::LED_BLUE, true);
  Config::setup();
  auto connection = Communication::SerialConnection(Serial);
  auto lcd_handler = DataHandler::LCDDisplay(
    SensorID::valve_1_state,
    SensorID::valve_2_state,
    // SensorID::valve_3_state,
    SensorID::injector_valve_state,
    SensorID::ignition_primary_ma,
    SensorID::ignition_secondary_ma,
    SensorID::healthy_actuators_count,
    SensorID::towerside_main_batt_mv,
    SensorID::towerside_actuator_batt_mv
  );
  auto encoder = Communication::HexEncoder<ActuatorCommand>();
  auto decoder = Communication::HexDecoder<SensorData>();
  auto receiver = Communication::MessageReceiver<SensorData>(decoder, connection,
    &lcd_handler
  );
  auto sender = Communication::MessageSender<ActuatorCommand>(encoder, connection);

  unsigned long last_message_sent = 0;
  ActuatorCommand last_switch_positions = DAQ::get_switch_positions();
  digitalWrite(Pinout::LED_BLUE, false); // startup finished
  while (true) {
    Tickable::trigger_tick();
    if (millis() - last_message_sent > Config::SEND_STATUS_INTERVAL_MS) {
      last_message_sent = millis();

      bool armed = !digitalRead(Pinout::KEY_SWITCH_IN);
      if (armed) {
        last_switch_positions = DAQ::get_switch_positions();
      }
      for (uint8_t i = 0; i < sizeof(Pinout::MISSILE_LEDS) / sizeof(Pinout::MISSILE_LEDS[0]); i++) {
        digitalWrite(Pinout::MISSILE_LEDS[i], !armed);
      }

      sender.send(last_switch_positions);
    }
    bool towerside_alive = connection.seconds_since_contact() < Config::MESSAGE_WARNING_INTERVAL_S;
    digitalWrite(Pinout::LED_GREEN, towerside_alive);
    digitalWrite(Pinout::LED_RED, !towerside_alive);
  }
}

void loop() {
}
