#ifndef LCD_H
#define LCD_H

#ifdef __cplusplus
extern "C" {
#endif

#include "shared_types.h"
#include <string.h> 
void lcd_init(); //called in setup
void lcd_update(daq_holder_t *input_dat); //called every time in loop()
#ifdef __cplusplus
}
#endif

#endif
