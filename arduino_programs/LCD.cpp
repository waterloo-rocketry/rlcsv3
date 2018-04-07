#include "LCD.h"
#include "LiquidCrystal.h"
#include "client_pin_defines.h"
#include "sd_handler.h"
//note this does not do formatting, so do that yourself
void lcd_nprint(int x, int y, int length, char *str);
void lcd_print(int x, int y, char c);
void output_labels();
#include <string.h>

static daq_holder_t last_daq;
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
    //sets every single bit in last_daq to 0 (which should be the default)
    //TODO aidan can you check that this works? I'm not sure if arduino
    //supports memset
    memset(&last_daq, 0, sizeof(last_daq));

    //lcd.print should wrap properly
    //TODO aidan can you check that this
    //properly writes the defaults when called?
    lcd.print("P1:    P2:    P3:   "
              "V1:    V2:    V3:   "
              "I1:    I2:    M:    "
              "AC:           LOG:NO");
}

/*  ----------------------
 *  |P1:700 P2:014 P3:016|
 *  |I1:0.0 I2:0.0 M:64.5|
 *  |V1:OPN V2:CLS V3:OPN|
 *  |AC:EXT              |
 *  ----------------------
 */

void convert(uint16_t value, char* tempx) {
  sprintf(tempx, "%03u", value);
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
        lcd.setCursor(3, 1);
        convert(daq->ign_pri_current, temp);
        lcd.write(temp);
    }
    if(daq->ign_sec_current != last_daq.ign_sec_current) {
        last_daq.ign_sec_current = daq->ign_sec_current;
        lcd.setCursor(10, 1);
        convert(daq->ign_sec_current, temp);
        lcd.write(temp);
    }

    if(daq->rocket_mass != last_daq.rocket_mass) {
        last_daq.rocket_mass = daq->rocket_mass;
        lcd.setCursor(17, 1);
        convert(daq->rocket_mass, temp);
        lcd.write(temp);
    }

    //handle whether the SD card is working
    if(sd_active()){
        lcd.setCursor(18,3);
        lcd.write(sd_buffer_dirty() ? "DI" : "OK");
    }

    lcd.setCursor(3, 2);
    lcd_update_valve(daq->rfill_lsw_open, daq->rfill_lsw_closed, daq->rfill_current_open, daq->rfill_current_close, "MCL", "MOP", "CLS", "OPN");//rfill
    lcd.setCursor(10, 2);
    lcd_update_valve(daq->rvent_lsw_open,  daq->rvent_lsw_closed, daq->rvent_current_open, daq->rvent_current_close, "MCL", "MOP", "CLS", "OPN");//rvent
    /*
    //you can do the same for v3 here
    lcd.setCursor(3, 3);
    //IF YOU REMOVE THE LINE BELOW THEN EVERYTHING WORKS FINE, BUT THAT DOESNT MAKE SENSE!!! FOR SOME REASON IF YOU CALL THE lcd_update_valve FUNCTION WITH THE LINAC, IT DOESNT UPDATE ON LCD. THUS YOU HAVE TO MANUALLY COPY PASTE THE SAME FUNCTION FOR THE LINAC
    //lcd_update_valve(daq->linac_lsw_extend,  daq->linac_lsw_retract, daq->linac_current_open, daq->linac_current_close, "MRT", "MEX", "RET", "EXT", lcd);//linac where ls_extended is ls 1 on truth table
     switch(daq->linac_lsw_extend) { //switch 1
      case 0 :
        switch(daq->linac_lsw_retract) {//switch 2
          case 0:
            switch(daq->linac_current_open) {//current 1
              case 0:
                switch(daq->linac_current_close) {//current 2
                  case 0:
                    lcd.write("ER1");
                    break;
                  case 1:
                    lcd.write("MRT");
                    break;
                }
                break;
              case 1:
                switch(daq->linac_current_close) {//current 2
                  case 0:
                    lcd.write("MXT");
                    break;
                  case 1:
                    lcd.write("ER2");
                    break;
                }
                break;
            }
            break;
          case 1:
             switch(daq->linac_current_open) {//current 1
              case 0:
                switch(daq->linac_current_close) {//current 2
                  case 0:
                    lcd.write("RET");
                    break;
                  case 1:
                    lcd.write("ER3");
                    break;
                }
                break;
              case 1:
                switch(daq->linac_current_close) {//current 2
                  case 0:
                    lcd.write("ER4");
                    break;
                  case 1:
                    lcd.write("ER5");
                    break;
                }
                break;
            }
            break;
        }
        break;
      case 1 :
        switch(daq->linac_lsw_retract) {//switch 2
          case 0:
            switch(daq->linac_current_open) {//current 1
              case 0:
                switch(daq->linac_current_close) {//current 2
                  case 0:
                    lcd.write("EXT");
                    break;
                  case 1:
                    lcd.write("ER6");
                    break;
                }
                break;
              case 1:
                switch(daq->linac_current_close) {//current 2
                  case 0:
                    lcd.write("ER7");
                    break;
                  case 1:
                    lcd.write("ER8");
                    break;
                }
                break;
            }
            break;
          case 1:
             switch(daq->linac_current_open) {//current 1
              case 0:
                switch(daq->linac_current_close) {//current 2
                  case 0:
                    lcd.write("ER9");
                    break;
                  case 1:
                    lcd.write("ERA");
                    break;
                }
                break;
              case 1:
                switch(daq->linac_current_close) {//current 2
                  case 0:
                    lcd.write("ERB");
                    break;
                  case 1:
                    lcd.write("ERC");
                    break;
                }
                break;
            }
            break;
        }
        break;
    }
    */
}

void lcd_update_valve(unsigned char lsw_open,
                      unsigned char lsw_closed,
                      unsigned char i_open,
                      unsigned char i_close,
                      const char* msg1, //closing
                      const char* msg2, //opening
                      const char* msg3, //closed
                      const char* msg4) //open
{
    //for now, just run off of the limit switches
    //this means the output is always open, closed, or unknown
    if(!lsw_open && lsw_closed) {
        lcd.write(msg3);
    } else if (lsw_open && !lsw_closed) {
        lcd.write(msg4);
    } else {
        lcd.write("UKN");
    }
}
