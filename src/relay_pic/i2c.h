#ifndef I2C_H
#define	I2C_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <xc.h>
#include <pic16f1826.h>

//Initializes i2c module
void i2c_slave_init(uint16_t address);

//interrupt handling of i2c signal
void i2c_handle_interrupt(void);

#endif	/* I2C_H */

