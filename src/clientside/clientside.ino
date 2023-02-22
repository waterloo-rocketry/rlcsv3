#include "common/communication.hpp"
#include "config.hpp"
#include "hardware.hpp"
#include "lcd.hpp"

void setup() {
  hardware::setup();
  hardware::set_status_startup();
  lcd::setup();

  Serial.begin(115200); // USB connection
  Serial3.begin(9600);  // Towerside connection

  Communicator<ActuatorMessage, SensorMessage> communicator{
      Serial3, config::COMMUNICATION_RESET_MS};
  unsigned long last_sent_time = 0;
  ActuatorMessage last_switch_positions;

  hardware::set_status_disconnected();
  // Avoid the status showing as connected for the first few seconds on
  // startup if we aren't really
  bool any_messages_received = false;
  bool has_been_armed = false;
  while (true) {
    communicator.read_byte();
    SensorMessage msg;
    if (communicator.get_message(&msg)) {
      any_messages_received = true;
      lcd::lcd_update(msg);
    }

    bool has_contact = communicator.seconds_since_last_contact() <
                       config::COMMUNICATION_TIMEOUT_S;
    if (has_contact && any_messages_received) {
      hardware::set_status_connected();
    } else {
      hardware::set_status_disconnected();
    }

    bool armed = hardware::is_armed();
    hardware::set_missile_leds(armed);
    if (armed) {
      last_switch_positions = config::build_command_message();
      has_been_armed = true;
    }

    if ((millis() > last_sent_time + config::COMMAND_MESSAGE_INTERVAL_MS) && has_been_armed) {
      // condition: passed COMMAND_MESSAGE_INTERVAL_MS since last time sent message AND client side has been armed before
      last_sent_time = millis();
      communicator.send(last_switch_positions);
    }
  }
}

void loop() {}
