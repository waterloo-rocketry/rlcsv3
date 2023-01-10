#ifndef LCD_HPP
#define LCD_HPP

#include "config.hpp"

void LCDInit();

void LCDUpdate(SensorContainer<uint16_t> msg);

#endif
