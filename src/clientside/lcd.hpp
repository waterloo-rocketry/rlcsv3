#ifndef LCD_HPP
#define LCD_HPP

#include "config.hpp"

namespace lcd {
void lcd_init();
void lcd_update(SensorMessage msg);
}; // namespace lcd

#endif
