#ifndef I2C_H
<<<<<<< HEAD
#define	I2C_H
=======
#define I2C_H
>>>>>>> 4e0c8d71b3290d9faf8db479f6ec01670aabe4c2

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <xc.h>
#include <pic16f1826.h>
#include "relay_general.h"

//Initializes i2c module
void i2c_slave_init(uint16_t address);

//interrupt handling of i2c signal
void i2c_handle_interrupt(void);

<<<<<<< HEAD
#endif	/* I2C_H */
=======
#endif /* I2C_H */
>>>>>>> 4e0c8d71b3290d9faf8db479f6ec01670aabe4c2

