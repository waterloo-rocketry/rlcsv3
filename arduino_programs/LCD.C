#include "LCD.h"
//note this does not do formatting, so do that yourself
void lcd_nprint(int x, int y, int length, char *str);
void lcd_print(int x, int y, char c);
void output_labels();
#include <string.h> 

static daq_holder_t last_daq;

void lcd_init(LiquidCrystal lcd)
{
//just put in some default values to the buffered holders
    last_daq.pressure1           = 0;
    last_daq.pressure2           = 0;
    last_daq.pressure3           = 0;
    last_daq.pressure2           = 0;
    last_daq.rocket_mass         = 0;
    last_daq.ign_pri_current     = 0;
    last_daq.ign_sec_current     = 0;
   
    last_daq.rfill_current_open  = 0;
    last_daq.rfill_current_close = 0;
    last_daq.rvent_current_open  = 0;
    last_daq.rvent_current_close = 0;
    last_daq.rfill_lsw_open      = 0;
    last_daq.rfill_lsw_closed    = 0;
    last_daq.rvent_lsw_open      = 0;
    last_daq.rvent_lsw_closed    = 0;
    
    last_daq.linac_current_open  = 0;
    last_daq.linac_current_close = 0;
    last_daq.linac_lsw_extend    = 0;
    last_daq.linac_lsw_retract   = 0;
//set labels
    // loop over the columns:
    const char* labels[] = {"P1:000 P2:000 P3:000", "I1:000 I2:000 M:0000", "V1:CLS V2:CLS V3:CLS", "AC:EXT                 "};
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
    
    if(daq->pressure1 != last_daq.pressure1) {
        last_daq.pressure1 = daq->pressure1;
        lcd.setCursor(3, 0);
        lcd.write("000");
        char temp1[] = "001";
        lcd.setCursor(3+moveCursor(daq->pressure1), 0);
        lcd.write(strcpy(temp1, convert(daq->pressure1)));     
    }

    if(daq->pressure2 != last_daq.pressure2) {
        last_daq.pressure2 = daq->pressure2;
        lcd.setCursor(10, 0);
        lcd.write("000");
        char temp2[] = "001";
        lcd.setCursor(10+moveCursor(daq->pressure2), 0);
        lcd.write(strcpy(temp2, convert(daq->pressure2))); 
    }
    if(daq->pressure3 != last_daq.pressure3) {
        last_daq.pressure3 = daq->pressure3;
        lcd.setCursor(17, 0);
        lcd.write("000");      
        char temp3[] = "111";
        lcd.setCursor(17+moveCursor(daq->pressure3), 0);
        lcd.write(strcpy(temp3, convert(daq->pressure3))); 
    }
    if(daq->ign_pri_current != last_daq.ign_pri_current) {
        last_daq.pressure2 = daq->pressure2;
        lcd.setCursor(3, 1);
        lcd.write("000");
        char temp4[] = "001";
        lcd.setCursor(3+moveCursor(daq->ign_pri_current), 1);
        lcd.write(strcpy(temp4, convert(daq->ign_pri_current))); 
    }
    if(daq->ign_sec_current != last_daq.ign_sec_current) {
        last_daq.pressure2 = daq->pressure2;
        lcd.setCursor(10, 1);
        lcd.write("000");
        char temp5[] = "001";
        lcd.setCursor(10 + moveCursor(daq->ign_sec_current), 1);
        lcd.write(strcpy(temp5, convert(daq->ign_sec_current))); 
    }
    
    if(daq->rocket_mass != last_daq.rocket_mass) {
        lcd.setCursor(16, 1);
        lcd.write("0000");
        char temp6[] = "0001";
        lcd.setCursor(17 + moveCursor(daq->rocket_mass), 1);
        lcd.write(strcpy(temp6, convert(daq->rocket_mass)));        
    }
    lcd.setCursor(3, 2);
    lcd_update_valve(daq->rfill_lsw_open, daq->rfill_lsw_closed, daq->rfill_current_open, daq->rfill_current_close, "MCL", "MOP", "CLS", "OPN", lcd);//rfill
    lcd.setCursor(10, 2);
    lcd_update_valve(daq->rvent_lsw_open,  daq->rvent_lsw_closed, daq->rvent_current_open, daq->rvent_current_close, "MCL", "MOP", "CLS", "OPN", lcd);//rvent 
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
}

void lcd_update_valve(unsigned char state1, unsigned char state2, unsigned char state3, unsigned char state4, const char* msg1, const char* msg2, const char* msg3, const char* msg4, LiquidCrystal lcd) {
 switch(state1) { //switch 1
      case 0 : 
        switch(state2) {//switch 2
          case 0:
            switch(state3) {//current 1
              case 0:
                switch(state4) {//current 2
                  case 0:
                    lcd.write("ER1");
                    break;
                  case 1:
                    lcd.write(msg1);
                    break;
                }
                break;
              case 1:
                switch(state4) {//current 2
                  case 0:
                    lcd.write(msg2);
                    break;
                  case 1:
                    lcd.write("ER2");
                    break;
                }
                break;              
            }
            break;
          case 1:
             switch(state3) {//current 1
              case 0:
                switch(state4) {//current 2
                  case 0:
                    lcd.write(msg3);
                    break;
                  case 1:
                    lcd.write("ER3");
                    break;
                }
                break;
              case 1:
                switch(state4) {//current 2
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
        switch(state2) {//switch 2
          case 0:
            switch(state3) {//current 1
              case 0:
                switch(state4) {//current 2
                  case 0:
                    lcd.write(msg4);
                    break;
                  case 1:
                    lcd.write("ER6");
                    break;
                }
                break;
              case 1:
                switch(state4) {//current 2
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
             switch(state3) {//current 1
              case 0:
                switch(state4) {//current 2
                  case 0:
                    lcd.write("ER9");
                    break;
                  case 1:
                    lcd.write("ERA");
                    break;
                }
                break;
              case 1:
                switch(state4) {//current 2
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
}

