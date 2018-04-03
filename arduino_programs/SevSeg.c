#include "SevSeg.h"
#ifdef CLIENT
#include "client_pin_defines.h"
#else
#include "tower_pin_defines.h"
#endif
//#include <avr/io.h>
#include<Stdint.h>
#define BLANK_IDX 11 // Must match with 'digitCodeMap'
#define DASH_IDX 12

//array of segements that must be displayed to display the correct number
static const uint8_t digitCodeMap[] = {
  //GFEDCBA  Segments      7-segment map:
  0b0111111, // 0   "0"          AAA
  0b0000110, // 1   "1"         F   B
  0b1011011, // 2   "2"         F   B
  0b1001111, // 3   "3"          GGG
  0b1100110, // 4   "4"         E   C
  0b1101101, // 5   "5"         E   C
  0b1111101, // 6   "6"          DDD
  0b0000111, // 7   "7"
  0b1111111, // 8   "8"
  0b1101111, // 9   "9"
  0b1110111, // A "A"
  0b1111100, // b "b"
  0b0111001, // C "C"
  0b1011110, // d "d"
  0b1111001, // E "E"
  0b1110001 // F "F"
  //"0000000", // 32  ' '  BLANK
  //"0000001", // 45  '-'  DASH
};

const uint8_t * digitCodes[2];

static const unsigned digitPinsIn[] = {
    PIN_SEVENSEG_D1,
    PIN_SEVENSEG_D2
};
static const unsigned segmentPinsIn[] = {
    PIN_SEVENSEG_A,
    PIN_SEVENSEG_B,
    PIN_SEVENSEG_C,
    PIN_SEVENSEG_D,
    PIN_SEVENSEG_E,
    PIN_SEVENSEG_F,
    PIN_SEVENSEG_G
};

//functions
void setDigitCodes(uint8_t digits);

void start_SevSeg () {//sets the values of the digitpin and segment pins in the struct, pinmode all of the pins, and turns them all off

  pinMode(digitPinsIn[0], OUTPUT);
  pinMode(digitPinsIn[1], OUTPUT);

  for (int x = 0; x < 7; x++) {
    pinMode(segmentPinsIn[x], OUTPUT);	//sets digits pins as outputs
    digitalWrite(segmentPinsIn[x], HIGH);	//turns segment pins off
  }
}

void refresh_SevSeg() {//refreshes display and lights up the segments
  //write to pin 1
  digitalWrite(digitPinsIn[0], HIGH);//turns first segment pin on
  digitalWrite(digitPinsIn[1], LOW);//turns off second digit
  for (int i = 0; i < 2; i++) { //goes throught each digit code and lights up appriopriate segment for each one
    for (int j = 0; j < 7; j++) {
      digitalWrite(segmentPinsIn[j], (*digitCodes[i] & (1<<j)) ? LOW : HIGH);
    }
    delay(10);//this is so that 2 numbers can be displayed instantaneously
    //swap two digits, on next iteration of loop we write to other two digits
    digitalWrite(digitPinsIn[0], LOW);//turns off first digit
    digitalWrite(digitPinsIn[1], HIGH);//turns on second digit
  }
}

void setNewNum_SevSeg (uint8_t numToShow) {//sets the number the user wants
  setDigitCodes(numToShow);
}

void setDigitCodes(uint8_t numToShow) { //this function gets the digit code of each number in the 'digit' array
  // Set the digitCode for each digit in the display(digit array)
  digitCodes[0] = digitCodeMap + (numToShow & 0xF);
  digitCodes[1] = digitCodeMap + ((numToShow >> 4) & 0xF);
}
