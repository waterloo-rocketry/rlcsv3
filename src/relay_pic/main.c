/* 
 * File:   pinConfigMain.c
 * Author: zacha
 *
 * Created on March 1, 2020, 3:21 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include <pic16f1826.h>
#include "mcc_generated_files/adc.h"
#include "mcc_generated_files/mcc.h"

typedef char bool;
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;

#define TRUE 1
#define FALSE 0

#define POWER (1 << 2)
#define SELECT (1 << 3)
#define LIM1 (1 << 7)
#define LIM2 (1 << 6)
#define DIP1 (1 << 4)
#define DIP2 (1)
#define DIP3 (1 << 2)
#define DIP4 (1 << 3)
#define LED3 (1 << 5)
#define CURR_SENSE1 (1 << 1)
#define CURR_SENSE2 (1)

#pragma config WDTE = OFF
#pragma FOSC = INTOSCIO

bool d1, d2, d3, d4;
uint16_t result;

void readAnalogInputs() {
    for (int i = 0; i < 1000; i++) {}
    ADCON0 = 0x01; // Turn ADC on
    ADCON0 |= 1 << 1; // set b[1] "go" bit
    uint8_t doneBit;
    do { //wait for ADC to complete (go bit switches to 0 automatically when done)
        doneBit = ADCON0 & (1 << 1);
    } while (doneBit); //while go bit is on (AD conversion in progress)

    result = (ADRESH << 8) | ADRESL; //combine two 8bit values into a 16bit value

    ADCON0 = 0x00; //Turn ADC off return;
}

void setPower(bool out) { 
    if (out) { LATA |= POWER;} 
    else { LATA &= ~POWER; }
}

void setSelect(bool out) {
    if (out) { LATA |= SELECT;} 
    else { LATA &= ~SELECT; }
}

void setLim1(bool out) { // XXX
    if (out) { LATA |= LIM1;} 
    else { LATA &= ~LIM1; }
}

void setLim2(bool out) {
    if (out) { LATA |= LIM2; } 
    else { LATA &= ~LIM2; }
}

void setLed3(bool out) {
    if (out) { LATB |= LED3; }
    else { LATB &= ~LED3; }
}

bool readDIP1() { return (PORTA & DIP1) ? 1 : 0; }
bool readDIP2() { return (PORTB & DIP2) ? 1 : 0; }
bool readDIP3() { return (PORTB & DIP3) ? 1 : 0; }
bool readDIP4() { return (PORTB & DIP4) ? 1 : 0; }

void setup() {
    TRISA = CURR_SENSE1 | CURR_SENSE2 | DIP1;
    TRISB = DIP2 | DIP3 | DIP4;
    ANSELA = CURR_SENSE1 | CURR_SENSE2; //Set RA0 and RA1 as analog inputs.

    // Configure ADC module 
    // b[7] sets right justification, b[6:4] sets CS = FRC,
    // b[2]+b[1:0] sets Vss and Vdd as references.

    ADCON1 = 0b11110000;
}

int main(int argc, char** argv) {
    setup();
    setPower(TRUE);
    setSelect(TRUE);
    setLim1(TRUE);
    setLim2(TRUE);
    while (1) {
        // Infinite Loop
        d1 = readDIP1();
        d2 = readDIP2();
        d3 = readDIP3();
        d4 = readDIP4();
        readAnalogInputs();
    }
    return (EXIT_SUCCESS);
}

