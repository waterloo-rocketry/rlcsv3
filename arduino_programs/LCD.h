#ifndef LCD_H
#define LCD_H

#ifdef __cplusplus
extern "C" {
#endif

#include "shared_types.h"
#include <string.h> 
void lcd_init(); //called in setup
void lcd_update(daq_holder_t *input_dat); //called every time in loop()
void lcd_update_valve(unsigned char state1, unsigned char state2, unsigned char state3, unsigned char state4, const char* msg1, const char* msg2, const char* msg3, const char* msg4);
#ifdef __cplusplus
}
#endif

#endif
