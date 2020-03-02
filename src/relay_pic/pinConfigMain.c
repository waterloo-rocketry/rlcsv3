/* 
 * File:   pinConfigMain.c
 * Author: zacha
 *
 * Created on March 1, 2020, 3:21 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <xc.h>

typedef char bool;

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

#pragma config WDTE = OFF
#pragma FOSC = INTOSCIO

bool d1, d2, d3, d4;

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
    if (out) { LATA |= LIM2;} 
    else { LATA &= ~LIM2; }
}

bool readDIP1() { return (PORTA & DIP1) ? 1 : 0; }
bool readDIP2() { return (PORTB & DIP2) ? 1 : 0; }
bool readDIP3() { return (PORTB & DIP3) ? 1 : 0; }
bool readDIP4() { return (PORTB & DIP4) ? 1 : 0; }

void setup() {
    TRISA = DIP1;
    ANSELA = 0;
    ANSELB = 0;
    TRISB = DIP2 | DIP3 | DIP4;
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
    }
    return (EXIT_SUCCESS);
}

