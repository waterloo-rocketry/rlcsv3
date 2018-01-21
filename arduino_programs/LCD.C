#include "LCD.h"
//note this does not do formatting, so do that yourself
void lcd_nprint(int x, int y, int length, char *str);
void lcd_print(int x, int y, char c);
void output_labels();
#include <string.h> 
daq_holder_t* last_daq;

void lcd_init(LiquidCrystal lcd)
{
//just put in some default values to the buffered holders
    last_daq->pressure1           = 0;
    last_daq->pressure2           = 0;
    last_daq->pressure3           = 0;
    last_daq->pressure2           = 0;
    last_daq->rocket_mass         = 0;
    last_daq->ign_pri_current     = 0;
    last_daq->ign_sec_current     = 0;
    last_daq->rfill_current_open  = 0;
    last_daq->rfill_current_close = 0;
    last_daq->rvent_current_open  = 0;
    last_daq->rvent_current_close = 0;
    last_daq->linac_current_open  = 0;
    last_daq->linac_current_close = 0;
    last_daq->rfill_lsw_open      = 0;
    last_daq->rfill_lsw_closed    = 0;
    last_daq->rvent_lsw_open      = 0;
    last_daq->rvent_lsw_closed    = 0;
    last_daq->linac_lsw_extend    = 0;
    last_daq->linac_lsw_retract   = 0;
//set labels
    // loop over the columns:
    char* labels[] = {"P1:000 P2:000 P3:000", "I1:000 I2:000 M:0000", "V1:CLS V2:CLS V3:CLS", "AC:EXT                 "};
    for (int  thisRow = 0; thisRow < 4; thisRow++) {
      for (int thisCol = 0; thisCol < 20; thisCol++) {
        // set the cursor position:
        lcd.setCursor(thisCol, thisRow);
        lcd.write(labels[thisRow][thisCol]);
        //delay(20);
      }
    }
    lcd_update(last_daq, lcd);
}

/*  ----------------------
 *  |P1:700 P2:014 P3:016|
 *  |I1:0.0 I2:0.0 M:64.5|
 *  |V1:OPN V2:CLS V3:OPN|
 *  |AC:EXT              |
 *  ----------------------
 */
char* convert(uint16_t value) {
  char tempx[3];
  sprintf(tempx, "%u", value); 
  return (tempx);
 }
 
int moveCursor(uint16_t value) {
  if(value < 10) {
    return 2;
  } else if (value < 100) {
    return 1;
  } else {
    return 0;
  }
}

void lcd_update(daq_holder_t* daq, LiquidCrystal lcd){
    //pressures first
    if(daq->pressure1 > 999) daq->pressure1 = 999;
    if(daq->pressure2 > 999) daq->pressure1 = 999;
    if(daq->pressure3 > 999) daq->pressure1 = 999;
    
    if(daq->pressure1 != last_daq->pressure1) {
      //last_daq->pressure1 = daq->pressure1;
        lcd.setCursor(3, 0);
        lcd.write("000");
        char* temp1 = "001";
        lcd.setCursor(3+moveCursor(daq->pressure1), 0);
        lcd.write(strcpy(temp1, convert(daq->pressure1)));     
    }

    if(daq->pressure2 != last_daq->pressure2) {
        //last_daq->pressure2 = daq->pressure2;
        lcd.setCursor(10, 0);
        lcd.write("000");
        char* temp2 = "001";
        lcd.setCursor(10+moveCursor(daq->pressure2), 0);
        lcd.write(strcpy(temp2, convert(daq->pressure2))); 
    }
    if(daq->pressure3 != last_daq->pressure3) {
      //last_daq->pressure3 = daq->pressure3;
        lcd.setCursor(17, 0);
        lcd.write("000");      
        char* temp3 = "111";
        lcd.setCursor(17+moveCursor(daq->pressure3), 0);
        lcd.write(strcpy(temp3, convert(daq->pressure3))); 
    }
    if(daq->ign_pri_current != last_daq->ign_pri_current) {
        //last_daq->pressure2 = daq->pressure2;
        lcd.setCursor(3, 1);
        lcd.write("000");
        char* temp4 = "001";
        lcd.setCursor(3+moveCursor(daq->ign_pri_current), 1);
        lcd.write(strcpy(temp4, convert(daq->ign_pri_current))); 
    }
    if(daq->ign_sec_current != last_daq->ign_sec_current) {
        //last_daq->pressure2 = daq->pressure2;
        lcd.setCursor(10, 1);
        lcd.write("000");
        char* temp5 = "001";
        lcd.setCursor(10 + moveCursor(daq->ign_sec_current), 1);
        lcd.write(strcpy(temp5, convert(daq->ign_sec_current))); 
    }
    
    if(daq->rocket_mass != last_daq->rocket_mass) {
        lcd.setCursor(16, 1);
        lcd.write("0000");
        char* temp6 = "0001";
        lcd.setCursor(17 + moveCursor(daq->rocket_mass), 1);
        lcd.write(strcpy(temp6, convert(daq->rocket_mass)));        
    }
}

