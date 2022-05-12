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
  Hardware::setup(); // set up hardware
  // blue LED to show we are starting up
  digitalWrite(Pinout::LED_BLUE, true);
  // initialize configuration arrays (switches, channels)
  Config::setup();
  // connect to towerside on the Serial port
  auto connection = Communication::SerialConnection(Serial);
  // Define the fields to be shown on the LCD. Right now these are just shown in order, 3 per line.
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
  // Define how we will encode and decode messages to/from towerside
  auto encoder = Communication::HexEncoder<ActuatorCommand>();
  auto decoder = Communication::HexDecoder<SensorData>();
  auto receiver = Communication::MessageReceiver<SensorData>(decoder, connection,
    &lcd_handler
  );
  auto sender = Communication::MessageSender<ActuatorCommand>(encoder, connection);

  unsigned long last_message_sent = 0;
  // store the latest armed switch positions so that we can keep commanding towerside if we get disarmed
  ActuatorCommand last_switch_positions;
  digitalWrite(Pinout::LED_BLUE, false); // startup finished

  while (true) {
    // Call the tick() methods on anything that inherits from Tickable
    Tickable::trigger_tick();
    // Time to send a command to towerside?
    if (millis() - last_message_sent > Config::SEND_STATUS_INTERVAL_MS) {
      last_message_sent = millis();

      // If we are armed, read the state of the switches. Otherwise just send the most recent state when we were armed
      bool armed = !digitalRead(Pinout::KEY_SWITCH_IN);
      if (armed) {
        last_switch_positions = DAQ::get_switch_positions();
      }
      // Light up the switch LEDs if we are armed
      for (uint8_t i = 0; i < sizeof(Pinout::MISSILE_LEDS) / sizeof(Pinout::MISSILE_LEDS[0]); i++) {
        digitalWrite(Pinout::MISSILE_LEDS[i], !armed); // active low
      }

      sender.send(last_switch_positions);
    }
    // Make the LED red if we haven't heard from towerside recently. Green otherwise.
    bool towerside_alive = connection.seconds_since_contact() < Config::MESSAGE_WARNING_INTERVAL_S;
    digitalWrite(Pinout::LED_GREEN, towerside_alive);
    digitalWrite(Pinout::LED_RED, !towerside_alive);
  }
}

// We should never get here but arduino makes us include it.
void loop() {
}
