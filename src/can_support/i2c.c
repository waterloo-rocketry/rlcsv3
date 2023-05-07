#include "i2c.h"
#include <xc.h>

void i2c_set_address(uint8_t address) {
    I2C1ADR0 = address << 1;
}

void i2c_initialize() {
    TRISC4 = 0;
    TRISC3 = 0;
    ODCONCbits.ODCC4 = 1;
    ODCONCbits.ODCC3 = 1;
    I2C1SDAPPS = 0x14; // C4
    RC4PPS = 0x22; // I2C 1 SDA
    I2C1SCLPPS = 0x13; // C3
    RC3PPS = 0x21; // I2C 1 SCL
    
    I2C1CON0bits.MODE = 0b000; // Slave with 7 bit addressing
    I2C1PIEbits.WRIE = 1;
    PIE3bits.I2C1TXIE = 1;
    PIE3bits.I2C1IE = 1;
    I2C1CNT=0xFF;
    
    I2C1CON0bits.EN = 1;
}

void i2c_handle_interrupt() {
    // If this is an I2C write
    if (I2C1STAT1bits.RXBF) {
        uint8_t cmd = I2C1RXB;
        // we care about the second from last bit
        LATC2 = (cmd & 0b10) > 0;
        I2C1CON1bits.ACKDT = 0;
        I2C1PIRbits.WRIF = 0;
    }
    // If this is an I2C read
    if (PIR3bits.I2C1TXIF) {
        I2C1TXB = 0;
    }
    PIR3bits.I2C1IF = 0;
    I2C1CON0bits.CSTR = 0;
}