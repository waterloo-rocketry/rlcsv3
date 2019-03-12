#include "LCD.h"
#include "LiquidCrystal.h"
#include "client_pin_defines.h"
#include "sd_handler.h"
//note this does not do formatting, so do that yourself
void lcd_nprint(int x, int y, int length, char *str);
void lcd_print(int x, int y, char c);
void output_labels();
#include <string.h>

//setup last daq to hold impossible values
//so that when we get the first data from the tower,
//it updates with those values
static daq_holder_t last_daq = {
    .pressure1 = 999,
    .pressure2 = 999,
    .pressure3 = 999,
    .rocket_mass = 0xFFFF,
    .ign_pri_current = 0xFFFF,
    .ign_sec_current = 0xFFFF,
    .rfill_lsw_open = 0,
    .rfill_lsw_closed = 0,
    .rvent_lsw_open = 0,
    .rvent_lsw_closed = 0,
    .rocketvent_lsw_open = 0,
    .rocketvent_lsw_closed = 0,
    .injectorvalve_lsw_open = 0,
    .injectorvalve_lsw_closed = 0,
    .linac_lsw_extend = 0,
    .linac_lsw_retract = 0
};

static LiquidCrystal lcd(
    PIN_LCD_RS,
    PIN_LCD_EN,
    PIN_LCD_D4,
    PIN_LCD_D5,
    PIN_LCD_D6,
    PIN_LCD_D7);

void lcd_init()
{
    lcd.begin(20,4);

    lcd.setCursor(0,0);
    lcd.print("P1:    P2:    P3:   ");
    lcd.setCursor(0,1);
    lcd.print("RF:    RV:    TV:   ");
    lcd.setCursor(0,2);
    lcd.print("I1:    I2:    IJ:   ");
    lcd.setCursor(0,3);
    lcd.print("AC:    M:     LOG:NO");
}

void convert(uint16_t value, char* tempx) {
  sprintf(tempx, "%03u", value);
 }

static void lcd_update_valve(unsigned char lsw_open,
                      unsigned char lsw_closed,
                      const char* msg1, //closed
                      const char* msg2) //open
{
    //for now, just run off of the limit switches
    //this means the output is always open, closed, or unknown
    if(!lsw_open && lsw_closed) {
        lcd.write(msg1);
    } else if (lsw_open && !lsw_closed) {
        lcd.write(msg2);
    } else {
        lcd.write("UKN");
    }
}

void lcd_update(daq_holder_t* daq){

    //pressures first
    if(daq->pressure1 > 999) daq->pressure1 = 999;
    if(daq->pressure2 > 999) daq->pressure1 = 999;
    if(daq->pressure3 > 999) daq->pressure1 = 999;

    char temp[10];
    if(daq->pressure1 != last_daq.pressure1) {
        last_daq.pressure1 = daq->pressure1;
        convert(daq->pressure1, temp);
        lcd.setCursor(3, 0);
        lcd.write(temp);
    }

    if(daq->pressure2 != last_daq.pressure2) {
        last_daq.pressure2 = daq->pressure2;
        lcd.setCursor(10, 0);
        convert(daq->pressure2, temp);
        lcd.write(temp);
    }
    if(daq->pressure3 != last_daq.pressure3) {
        last_daq.pressure3 = daq->pressure3;
        lcd.setCursor(17, 0);
        convert(daq->pressure3, temp);
        lcd.write(temp);
    }
    if(daq->ign_pri_current != last_daq.ign_pri_current) {
        last_daq.ign_pri_current = daq->ign_pri_current;
        lcd.setCursor(3, 2);
        convert(daq->ign_pri_current, temp);
        lcd.write(temp);
    }
    if(daq->ign_sec_current != last_daq.ign_sec_current) {
        last_daq.ign_sec_current = daq->ign_sec_current;
        lcd.setCursor(10, 2);
        convert(daq->ign_sec_current, temp);
        lcd.write(temp);
    }

    if(daq->rocket_mass != last_daq.rocket_mass) {
        last_daq.rocket_mass = daq->rocket_mass;
        lcd.setCursor(10, 3);
        convert(daq->rocket_mass, temp);
        lcd.write(temp);
    }

    //handle whether the SD card is working
    if(sd_active()){
        lcd.setCursor(18,3);
        lcd.write(sd_buffer_dirty() ? "DI" : "OK");
    }

    lcd.setCursor(3, 1);
    lcd_update_valve(daq->rfill_lsw_open, daq->rfill_lsw_closed, "CLS", "OPN");//rfill
    lcd.setCursor(10, 1);
    lcd_update_valve(daq->rvent_lsw_open,  daq->rvent_lsw_closed, "CLS", "OPN");//rvent
    lcd.setCursor(17,1);
    lcd_update_valve(daq->rocketvent_lsw_open, daq->rocketvent_lsw_closed, "CLS", "OPN");//tank valve
    lcd.setCursor(17,2);
    lcd_update_valve(daq->injectorvalve_lsw_open, daq->injectorvalve_lsw_closed, "CLS", "OPN");
    lcd.setCursor(3, 3);
    lcd_update_valve(daq->linac_lsw_extend, daq->linac_lsw_retract, "RET", "EXT");//linear actuator
}
