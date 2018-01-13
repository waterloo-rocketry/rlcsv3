#ifndef SevSeg_h
#define SevSeg_h
#include<stdint.h>
#include"arduino.h"


struct SevSeg {
	char digitPins[2];//INPUT/OUTPUT
	char segmentPins[8];//SEGMENT PIN (ON/OFF)
	char digitCodes[2][7]; //Array of bytes needed to display the number
 int digits[2];
};

void start (char digitPinsIn[2], char segmentPinsIn[2], struct SevSeg* sevSegDisplay);//function that runs at the beginning. this sets up the display
void refresh(struct SevSeg* sevSegDisplay);
void setSegments(char segs[], struct SevSeg* sevSegDisplay);
void setNewNum (long numToShow, struct SevSeg* sevSegDisplay);//sets desired integer
void blank(struct SevSeg* sevSegDisplay); //displays a blank seg
void clearSeg(char digitPinsIn[2], char segmentPinsIn[2], struct SevSeg* sevSegDisplay);//clears the pins at the end of the program.
void setDigitCodes(int digits[], struct SevSeg* sevSegDisplay); //sets'digitcodes' that is required to display the input number.
void findDigits(long numToShow, int digits[], struct SevSeg* sevSegDisplay);
#endif
