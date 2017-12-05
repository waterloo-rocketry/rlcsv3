#ifndef CLIENT_PIN_DEFINES_H
#ifndef CLIENT_PIN_DEFINES_H

//right now the pins are assigned arbitrary numbers
//TODO, assign the actual pin numbers to these
//(this can't be done until we've actually got the thing
//layed out)

//pins for the switches
#define PIN_SWITCH_REMOTEFILL    1
#define PIN_SWITCH_REMOTEVENT    2
#define PIN_SWITCH_ROCKETVALVE   3
#define PIN_SWITCH_LINACTUATOR   4
#define PIN_SWITCH_IGNITION_PRI  5
#define PIN_SWITCH_IGNITION_SEC  6
#define PIN_SWITCH_IGNITION_FIRE 7

//pins for the LCD output
#define PIN_LCD_RS 8
#define PIN_LCD_EN 9
#define PIN_LCD_D0 10 //some lcds can run in 4 bit mode (only d4-d7)
#define PIN_LCD_D1 11 //I dont know if we can do that with this LCD, so
#define PIN_LCD_D2 12 //we're gonna start with 8 bit mode. TODO, see if
#define PIN_LCD_D3 13 //we can do this with only 4 pins
#define PIN_LCD_D4 14
#define PIN_LCD_D5 15
#define PIN_LCD_D6 16
#define PIN_LCD_D7 17

//pins for the status LEDs
#define PIN_LED_GREEN 18
#define PIN_LED_RED   19

//pins for the seven segment display
#define PIN_SEVENSEG_D1 20
#define PIN_SEVENSEG_D2 21
#define PIN_SEVENSEG_A  22
#define PIN_SEVENSEG_B  23
#define PIN_SEVENSEG_C  24
#define PIN_SEVENSEG_D  25
#define PIN_SEVENSEG_E  26
#define PIN_SEVENSEG_F  27
#define PIN_SEVENSEG_G  28
#define PIN_SEVENSEG_DP 29

#endif //ifndef CLIENT_PIN_DEFINES_H
