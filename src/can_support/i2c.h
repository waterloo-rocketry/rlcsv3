#ifndef I2C_H
#define I2C_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <xc.h>
#include <pic18f26k83.h>

//Initializes i2c module
void i2c_slave_init();

//interrupt handling of i2c signal
void i2c_handle_interrupt(void);

#endif /* I2C_H */
