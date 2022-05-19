#include "daq.hpp"
#include "config.hpp"

namespace DAQ {

// Collect data from all of the sensors and put it into a SensorData object
SensorData get_sensor_message() {
  SensorData msg;
  for (uint8_t i = 0; i < NUM_SENSORS; i++) {
    SensorID::SensorID id = static_cast<SensorID::SensorID>(i);
    msg.set_sensor(id, Config::get_sensor(id)->get_value());
  }
  return msg;
}

}
