#include "common/communication.hpp"
#include "config.hpp"

void setup() {
  Serial.begin(115200);
  Wire.begin();
  Wire.setClock(10000);
  Wire.setWireTimeout(1000, true); // 1000 uS = 1mS timeout, true = reset the bus in this case

  Communicator<SensorContainer<uint16_t>, ActuatorContainer<bool>> communicator {Serial, config::COMMUNICATION_RESET_MS};
  unsigned long last_sensor_msg_time = 0;
  ActuatorContainer<bool> last_cmd;
  
  // We loop here so that the variables defined above are in scope
  while (true) {
    communicator.read_byte();
    ActuatorContainer<bool> cmd;
    if (communicator.get_message(&cmd)) {
      if (cmd == last_cmd) {
        config::apply(cmd);
      }
      last_cmd = cmd;
    }

    if (communicator.seconds_since_last_contact() > config::COMMUNICATION_TIMEOUT_S) {
      config::apply_safe_state();
    }

    if (millis() > last_sensor_msg_time + config::SENSOR_MSG_INTERVAL_MS) {
      last_sensor_msg_time = millis();
      communicator.send(config::build_sensor_message());
    }
  }
}

void loop() {
}
