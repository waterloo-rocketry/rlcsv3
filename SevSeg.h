#ifndef SevSeg_h
#define SevSeg_h
#include<stdint.h>

#ifndef MAXNUMDIGITS
#define MAXNUMDIGITS 2 
#endif

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#endif


struct SevSeg {
	//instance var
	//int digitOn, digitOff, segmentOn, segmentOff; // 0 is false, 1 is true
	int numDigits;
	//int delayTime;
	char digitPins[MAXNUMDIGITS];//INPUT/OUTPUT
	char segmentPins[8];//SEGMENT PIN (ON/OFF)
	char digitCodes[MAXNUMDIGITS][7]; //Array of bytes needed to display the number
	uint8_t digits[2];
};

void start (int numDigitsIn, char digitPinsIn[MAXNUMDIGITS], char segmentPinsIn[MAXNUMDIGITS], struct SevSeg* sevSegDisplay);//function that runs at the beginning. this sets up the display
void refresh(struct SevSeg* sevSegDisplay);
void setSegments(char segs[], struct SevSeg* sevSegDisplay);
void setNewNum (uint8_t numToShow, struct SevSeg* sevSegDisplay);//sets desired integer
void blank(struct SevSeg* sevSegDisplay); //displays a blank seg
void clearSeg(char digitPinsIn[MAXNUMDIGITS], char segmentPinsIn[MAXNUMDIGITS], struct SevSeg* sevSegDisplay);//clears the pins at the end of the program.
void setDigitCodes(uint8_t digits[], struct SevSeg* sevSegDisplay); //sets'digitcodes' that is required to display the input number.
void findDigits(uint8_t numToShow, struct SevSeg* sevSegDisplay);
#endif
