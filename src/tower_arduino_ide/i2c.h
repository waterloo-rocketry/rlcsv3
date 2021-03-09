#ifndef I2C_H_
#define I2C_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "shared_types.h"
#include <stdbool.h>

typedef enum {
  I2C_VALVE_1 = 1,
  I2C_VALVE_2 = 2,
  I2C_VALVE_3 = 3,
  I2C_VALVE_4 = 4,
  I2C_VALVE_INJECTOR = 5,
  I2C_IGNITION = 6
} valve_id_t;

void i2c_init(void);
void i2c_set_valve_power(valve_id_t valve, bool value);
void i2c_set_valve_select(valve_id_t valve, bool value);
valve_state_t i2c_get_state(valve_id_t valve);
void i2c_get_currents(valve_id_t valve, uint16_t *cur1, uint16_t *cur2);

#ifdef __cplusplus
}
#endif

#endif //ifndef I2C_H_
