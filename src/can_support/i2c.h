#ifndef I2C_H
#define	I2C_H

#include <stdint.h>

void i2c_set_address(uint8_t address);

void i2c_initialize(void);

void i2c_handle_interrupt(void);

#endif	/* I2C_H */