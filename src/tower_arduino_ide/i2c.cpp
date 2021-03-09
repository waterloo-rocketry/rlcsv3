#include "i2c.h"
#include "shared_types.h"
#include <Wire.h>
#include <stdbool.h>

#define POWER_BIT 0
#define SELECT_BIT 1

void i2c_init(void) {
  Wire.begin();
}

void i2c_set_valve_power(valve_id_t valve, bool value) {
  Wire.beginTransmission((uint8_t)valve);
  Wire.write(POWER_BIT | ((uint8_t)value << 1));
  Wire.endTransmission();
}

void i2c_set_valve_select(valve_id_t valve, bool value) {
  Wire.beginTransmission((uint8_t)valve);
  Wire.write(SELECT_BIT | ((uint8_t)value << 1));
  Wire.endTransmission();
}

valve_state_t i2c_get_state(valve_id_t valve) {
  Wire.requestFrom((uint8_t)valve, (uint8_t)1);
  uint8_t lims = Wire.read(); // bits 1 and 0 are lim2 and lim1 respectively
  if (lims == 0) return DAQ_VALVE_UNK;
  if (lims == 1) return DAQ_VALVE_OPEN; // TODO: Check if I got these limit switches right
  if (lims == 2) return DAQ_VALVE_CLOSED;
  return DAQ_VALVE_ILLEGAL;
}

void i2c_get_currents(valve_id_t valve, uint16_t *cur1, uint16_t *cur2) {
  Wire.requestFrom((uint8_t)valve, (uint8_t)5);
  Wire.read(); // Limit switch values, ignore.
  uint8_t adcl = Wire.read();
  uint8_t adch = Wire.read();
  *cur1 = (((uint16_t)adch << 8) | adcl) * 2;
  adcl = Wire.read();
  adch = Wire.read();
  *cur2 = (((uint16_t)adch << 8) | adcl) * 2;
}
