#ifndef LCD_DRIVER_H
#define LCD_DRIVER_H

#include "shared_types.h"

void init_lcd();
void update_lcd(actuator_state_t* actuators, daq_holder_t* daq);

#endif //ifndef LCD_DRIVER_H
