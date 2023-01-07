#include "common/communication.hpp"
#include "config.hpp"
#include "seven_seg.hpp"
#include "sensors.hpp"

void setup() {
  Serial.begin(115200);
  Serial2.begin(9600);
  Wire.begin();
  Wire.setClock(10000);
  Wire.setWireTimeout(1000, true); // 1000 uS = 1mS timeout, true = reset the bus in this case
  seven_seg::setup();
  sensors::setup();

  Communicator<SensorContainer<uint16_t>, ActuatorContainer<bool>> communicator {Serial2, config::COMMUNICATION_RESET_MS};
  unsigned long last_sensor_msg_time = 0;
  // The current towerside state. Each tick we command all actuators to take the action specified by it
  ActuatorContainer<bool> current_cmd = config::build_safe_state(ActuatorContainer<bool>());
  ActuatorContainer<bool> last_cmd; // The last received message from clientside, used for error detection
  
  // We loop here so that the variables defined above are in scope
  while (true) {
    communicator.read_byte();
    ActuatorContainer<bool> new_cmd;
    if (communicator.get_message(&new_cmd)) { // If we have a new message from clientside
      // If we got the same message last time around (aka no RF interference) and we are armed, apply the command
      if (new_cmd == last_cmd && sensors::is_armed()) {
        current_cmd = new_cmd;
      }
      last_cmd = new_cmd;
    }

    // If we have got a message from clientside recently
    bool has_contact = communicator.seconds_since_last_contact() < config::COMMUNICATION_TIMEOUT_S;
    sensors::set_contact(has_contact);
    if (!has_contact) {
      // Override clientside's command and go to safe state
      current_cmd = config::build_safe_state(current_cmd);
    }

    config::apply(current_cmd);
    seven_seg::display(current_cmd);
    seven_seg::tick();

    // Periodically send back our status
    if (millis() > last_sensor_msg_time + config::SENSOR_MSG_INTERVAL_MS) {
      last_sensor_msg_time = millis();
      communicator.send(config::build_sensor_message());
    }
  }
}

void loop() {
}
