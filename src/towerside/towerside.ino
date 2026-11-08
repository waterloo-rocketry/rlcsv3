  #include <SoftWire.h>
  #include "common/config.cpp" // cursed subfolder compile
  #include "common/communication.hpp"
  #include "config.hpp"
  #include "pinout.hpp"
  #include "seven_seg.hpp"
  #include "sensors.hpp"

  SoftWire SoftI2C(pinout::SOFT_SDA, pinout::SOFT_SCL);
  uint8_t I2CrxBuffer[32];
  uint8_t I2CtxBuffer[32];
  #define Wire SoftI2C

  void setup() {
    Serial.begin(115200);
    Serial2.begin(9600);

    SoftI2C.setRxBuffer(I2CrxBuffer, sizeof(I2CrxBuffer));
    SoftI2C.setTxBuffer(I2CtxBuffer, sizeof(I2CtxBuffer));

    Wire.begin();
    Wire.setClock(50000);
    // Wire.setWireTimeout(1000, true); // 1000 uS = 1mS timeout, true = reset the bus in this case
    seven_seg::setup();
    sensors::setup();

    pinMode(pinout::COMM_STATUS_LED,OUTPUT);
    pinMode(pinout::ARM_STATUS_LED,OUTPUT);
    digitalWrite(pinout::COMM_STATUS_LED,false);
    digitalWrite(pinout::ARM_STATUS_LED,false);

    Communicator<SensorMessage, ActuatorMessage> communicator {Serial2, config::COMMUNICATION_RESET_MS};
    unsigned long last_sensor_msg_time = 0;
    // The current towerside state. Each tick we command all actuators to take the action specified by it
    ActuatorMessage current_cmd = build_safe_state(ActuatorMessage());
    ActuatorMessage last_cmd; // The last received message from clientside, used for error detection
    
    // We loop here so that the variables defined above are in scope
    while (true) {
    // Process ALL incoming bytes waiting in the hardware serial buffer
    while (Serial2.available()) {
      communicator.read_byte();
      ActuatorMessage new_cmd;
      if (communicator.get_message(&new_cmd)) { // If a complete message was decoded
        if (new_cmd == last_cmd && sensors::is_armed()) {
          current_cmd = new_cmd;
        }
        last_cmd = new_cmd;
      }
    }

    // Handle contact timeouts
    uint16_t seconds_since_contact = communicator.seconds_since_last_contact();
    bool has_contact = seconds_since_contact < config::COMMUNICATION_TIMEOUT_S;
    sensors::set_contact(has_contact);
    digitalWrite(pinout::COMM_STATUS_LED, sensors::has_contact());
    digitalWrite(pinout::ARM_STATUS_LED, sensors::is_armed());
    if (seconds_since_contact >= config::SAFE_STATE_TIMEOUT_S) {
      current_cmd = build_safe_state(current_cmd);
    }

    // Execute I2C and display updates
    config::apply(current_cmd);
    seven_seg::display(current_cmd);
    seven_seg::tick();

    // Send telemetry
    if (millis() > last_sensor_msg_time + config::SENSOR_MSG_INTERVAL_MS) {
      last_sensor_msg_time = millis();
      communicator.send(config::build_sensor_message());
    }
  }
  }

  void loop() {
  }
