#ifndef LCD.h
#define LCD.h

#ifdef __cplusplus
extern "C" {
#endif

#include "shared_types.h"
#include <string.h> 
void lcd_init(LiquidCrystal lcd); //called in setup
char* value_to_string(uint16_t value, LiquidCrystal lcd, int row, int col);
void lcd_update(daq_holder_t *input_dat, LiquidCrystal lcd); //called every time in loop()
char* convert(uint16_t value);
int moveCursor(uint16_t value);
#ifdef __cplusplus
}
#endif

#endif
