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
void lcd_update_valve(unsigned char state1, unsigned char state2, unsigned char state3, unsigned char state4, const char* msg1, const char* msg2, const char* msg3, const char* msg4, LiquidCrystal lcd);
char* convert(uint16_t value);
int moveCursor(uint16_t value);
#ifdef __cplusplus
}
#endif

#endif
