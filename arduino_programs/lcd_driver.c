#include "lcd_driver.h"

//note this does not do formatting, so do that yourself
void lcd_nprint(int x, int y, int length, char *str);
void lcd_print(int x, int y, char c);
void output_labels();

daq_holder_t last_daq;

void init_lcd()
{
//just put in some default values to the buffered holders
    last_daq.pressure1           = 0;
    last_daq.pressure2           = 0;
    last_daq.rocket_mass         = 0;
    last_daq.ign_pri_current     = 0;
    last_daq.ign_sec_current     = 0;
    last_daq.rfill_current_open  = 0;
    last_daq.rfill_current_close = 0;
    last_daq.rvent_current_open  = 0;
    last_daq.rvent_current_close = 0;
    last_daq.linac_current_open  = 0;
    last_daq.linac_current_close = 0;
    last_daq.rfill_lsw_open      = 0;
    last_daq.rfill_lsw_closed    = 0;
    last_daq.rvent_lsw_open      = 0;
    last_daq.rvent_lsw_closed    = 0;
    last_daq.linac_lsw_extend    = 0;
    last_daq.linac_lsw_retract   = 0;

    output_labels();
    update_lcd(&last_daq);
}

/*  ----------------------
 *  |P1:700 P2:014 P3:016|
 *  |I1:0.0 I2:0.0 M:64.5|
 *  |V1:OPN V2:CLS V3:OPN|
 *  |AC:EXT              |
 *  ----------------------
 */
void update_lcd(daq_holder_t* daq){
    //output that to the proper place. Using hardcoded coords for now
    //TODO, maybe put those in a global struct for formatting?

    //pressures first
    if(daq->pressure1 > 999) daq->pressure1 = 999;
    if(daq->pressure1 != last_daq.pressure1) {
        lcd_print(3,0,daq->pressure1 % 100);
        
    }
}

void output_labels(){
    //top row
    lcd_nprint(0,0,3,"P1:");
    lcd_nprint(7,0,3,"P2:");
    lcd_nprint(14,0,3,"P3:");

    //second row
    lcd_nprint(0,1,3,"I1:");
    lcd_nprint(7,1,3,"I2:");
    lcd_nprint(14,1,3,"M:");

    //third row
    lcd_nprint(0,2,3,"I1:");
    lcd_nprint(7,2,3,"I2:");
    lcd_nprint(14,2,3,"M:");

    //bottom row
    lcd_nprint(0,3,3,"AC:");
    
}

void lcd_nprint(int x, int y, int len, char* str){
    //TODO make this smarter about line breaks and error checking
    for(int i = 0; i < len; i++)
        lcd_print(x+i, y, str[i]);
}
