#ifndef SHARED_TYPES_H
#define SHARED_TYPES_H

#include <stdint.h>
#include "config.hpp"
#include "communication/serializable.hpp"
#include "debug.hpp"

enum class ActuatorPosition {
  // Ordered this way so that position = open_lim + 2 * close_lim
  unknown = 0,
  open = 1,
  closed = 2,
  error = 3
};

// Store requested positions of each actuator. Clientside builds these to send to towerside.
class ActuatorCommand: Communication::Serializable {
  const static uint8_t SIZE = (NUM_ACTUATORS + 7) / 8; // ceiling division
  uint8_t actuator_states[SIZE] = {0}; // pack the actuators in a bit field
  public:
    void set_actuator(ActuatorID::ActuatorID id, bool value) {
      uint8_t i = id / 8;
      uint8_t bit = 1 << (id % 8);
      if (value) {
        actuator_states[i] |= bit;
      } else {
        actuator_states[i] &= ~bit; // bitwise not
      }
    }
    bool get_actuator(ActuatorID::ActuatorID id) const {
      uint8_t i = id / 8;
      uint8_t bit = 1 << (id % 8);
      return actuator_states[i] & bit ? true : false;
    }
    // Get the first 8 actuator states as a byte, useful for the 7-segment display and debugging.
    uint8_t get_byte() const {
      return actuator_states[0];
    }
    bool operator==(const ActuatorCommand &other) const {
      for (uint8_t i = 0; i < SIZE; i++) {
        if (actuator_states[i] != other.actuator_states[i]) {
          return false;
        }
      }
      return true;
    }

    // Serialization functions. We serialize as the packed bit array.
    static const uint8_t DATA_LENGTH = SIZE;
    bool decode(const uint8_t *buf) override {
      for (uint8_t i = 0; i < SIZE; i++) {
        actuator_states[i] = buf[i];
      }
      return true;
    }
    bool encode(uint8_t *buf) const override {
      for (uint8_t i = 0; i < SIZE; i++) {
        buf[i] = actuator_states[i];
      }
      return true;
    }
};

// Put this value in a sensor data field to signify an error.
const uint16_t SENSOR_ERR_VAL = 0xFFFF;

// Store a bunch of sensor data (actuator positions and currents, DAQ data) as 16-bit values.
// This is sent from towerside to clientside.
class SensorData: Communication::Serializable {
  uint16_t sensor_vals[NUM_SENSORS] {SENSOR_ERR_VAL};
  public:
    void set_sensor(SensorID::SensorID id, uint16_t val) {
      sensor_vals[id] = val;
    }
    uint16_t get_sensor(SensorID::SensorID id) const {
      return sensor_vals[id];
    }

    // Serialization functions. Encode as the sensor_vals array, most significant byte first.
    static const uint8_t DATA_LENGTH = NUM_SENSORS * 2; // two bytes per sensor
    bool decode(const uint8_t *buf) override {
      for (uint8_t i = 0; i < NUM_SENSORS; i++) {
        sensor_vals[i] = buf[i * 2] << 8;
        sensor_vals[i] |= buf[i * 2 + 1];
      }
      return true;
    }
    bool encode(uint8_t *buf) const override {
      for (uint8_t i = 0; i < NUM_SENSORS; i++) {
        buf[i * 2] = static_cast<uint8_t>(sensor_vals[i] >> 8);
        buf[i * 2 + 1] = static_cast<uint8_t>(sensor_vals[i] & 0xFF);
      }
      return true;
    }
};

#endif
