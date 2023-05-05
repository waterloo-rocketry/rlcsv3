#include "i2c.h"

#define _XTAL_FREQ 12000000
uint16_t i2cSlaveRecv; // Data received on i2c
uint16_t i2cSlaveSend; // Data to be sent on i2c

void i2c_slave_init() {
    I2C1CON0 = 0x01; 
    //con2 40
    I2C1PIE = 0x08;
    I2C1ADR0 = 0x00;
    I2C1ADR1 = 0x00;
    
    TRISC3 = 0;
    TRISC4 = 0;
    ODCONCbits.ODCC3 = 1;
    ODCONCbits.ODCC4 = 1;
    PIE3bits.I2C1IE = 1;
    PIE3bits.I2C1EIE = 1;
    PIE2bits.I2C1RXIE = 1;
    PIE3bits.I2C1TXIE = 1;
    I2C1PIEbits.PCIE = 0;
    I2C1PIEbits.ADRIE = 1;
    I2C1ERRbits.NACKIE = 0;
    I2C1PIEbits.WRIE = 0;
    I2C1CNT = 0x00;
    I2C1CON1bits.ACKCNT = 0;
    I2C1SDAPPS = 0x14;   //RC4->I2C1:SDA1;
    RC3PPS = 0x21;   //RC3->I2C1:SCL1;
    RC4PPS = 0x22;   //RC4->I2C1:SDA1;
    I2C1SCLPPS = 0x13;   //RC3->I2C1:SCL1;
    
    
    I2C1CON0bits.EN = 1;
}

void i2c_handle_interrupt(void) {
    //automatically match all addresses
    uint16_t temp;
    uint16_t data_temp;
    
    if(I2C1RXIF == 1) {
        data_temp = I2C1RXB;
    } else{
           
    temp = I2C1ADB0;
    
    I2C1PIR = 0;
     
    I2C1CON1bits.ACKDT = temp == 0x03;
    
    I2C1CON0bits.CSTR = 0;
    
    }
    
    
        
}


