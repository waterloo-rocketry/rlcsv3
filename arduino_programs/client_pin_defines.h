#ifndef CLIENT_PIN_DEFINES_H
#define CLIENT_PIN_DEFINES_H

//right now the pins are assigned arbitrary numbers
//TODO, assign the actual pin numbers to these
//(this can't be done until we've actually got the thing
//layed out)

//pins for the switches
#define PIN_SWITCH_REMOTEFILL    27
#define PIN_SWITCH_REMOTEVENT    26
#define PIN_SWITCH_ROCKETVALVE   4
#define PIN_SWITCH_LINACTUATOR   24 //for cf, this will be injector valve
#define PIN_SWITCH_INJECTOR      3
#define PIN_SWITCH_IGNITION_PRI  23
#define PIN_SWITCH_IGNITION_SEC  25
#define PIN_SWITCH_IGNITION_FIRE 22

//pins for the LCD output
#define PIN_LCD_RS 40
#define PIN_LCD_EN 42
#define PIN_LCD_D4 41
#define PIN_LCD_D5 43
#define PIN_LCD_D6 38
#define PIN_LCD_D7 39

//pins for the status LEDs
#define PIN_LED_GREEN 18
#define PIN_LED_RED   19

//pins for the seven segment display
#define PIN_SEVENSEG_D1 28
#define PIN_SEVENSEG_D2 29
#define PIN_SEVENSEG_A  30
#define PIN_SEVENSEG_B  31
#define PIN_SEVENSEG_C  32
#define PIN_SEVENSEG_D  33
#define PIN_SEVENSEG_E  34
#define PIN_SEVENSEG_F  35
#define PIN_SEVENSEG_G  36
#define PIN_SEVENSEG_DP 37

#endif //ifndef CLIENT_PIN_DEFINES_H
