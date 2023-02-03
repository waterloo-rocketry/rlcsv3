#include <xc.h>
#include "pin_manager.h"
#include "stdbool.h"




void SYSTEM_Initialize(void)
{
    PMD_Initialize();
    PIN_MANAGER_Initialize();
    OSCILLATOR_Initialize(); 
}


void PIN_MANAGER_Initialize(void) // 
{
    
//  LATx registers
    
    LATA = 0x00;
    LATB = 0x00;
    LATC = 0x00;

   
//  TRISx registers (default set PORTx to input)
    
    TRISA = 0xFF;
    TRISB = 0xFF;
    TRISC = 0xFF;

    
//  ANSELx registers (set all to digital I/0)
    
    ANSELC = 0x00; 
    ANSELB = 0x00;
    ANSELA = 0x00;

    
//  WPUx registers (no need since no analog)
   
   
    WPUE = 0x00;
    WPUB = 0x00;
    WPUA = 0x00;
    WPUC = 0x00;

    
//  ODx registers
    
    ODCONA = 0x00;
    ODCONB = 0x00;
    ODCONC = 0x00;

    
}


void PMD_Initialize(void) //still working on finding out what each function does
{
    // CLKRMD CLKR enabled; SYSCMD SYSCLK enabled; SCANMD SCANNER enabled; FVRMD FVR enabled; IOCMD IOC enabled; CRCMD CRC enabled; HLVDMD HLVD enabled; NVMMD NVM enabled; 
    PMD0 = 0x2; // 0 0 0 0 0 0 1 0
    // NCO1MD DDS(NCO1) enabed; TMR0MD TMR0 enabled; TMR1MD TMR1 enabled; TMR4MD TMR4 enabled; TMR5MD TMR5 enabled; TMR2MD TMR2 enabled; TMR3MD TMR3 enabled; TMR6MD TMR6 enabled; 
    PMD1 = 0x00; // 
    // ZCDMD ZCD enabled; DACMD DAC enabled; CMP1MD CMP1 enabled; ADCMD ADC enabled; CMP2MD CMP2 enabled; 
    PMD2 = 0x00;
    // CCP2MD CCP2 enabled; CCP1MD CCP1 enabled; CCP4MD CCP4 enabled; CCP3MD CCP3 enabled; PWM6MD PWM6 enabled; PWM5MD PWM5 enabled; PWM8MD PWM8 enabled; PWM7MD PWM7 enabled; 
    PMD3 = 0x00;
    // CWG3MD CWG3 enabled; CWG2MD CWG2 enabled; CWG1MD CWG1 enabled; 
    PMD4 = 0x00;
    // U2MD UART2 enabled; U1MD UART1 enabled; SPI1MD SPI1 enabled; I2C2MD I2C2 enabled; I2C1MD I2C1 enabled; 
    PMD5 = 0x00;
    // DSMMD DSM1 enabled; CLC3MD CLC3 enabled; CLC4MD CLC4 enabled; SMT1MD SMT1 enabled; SMT2MD SMT2 enabled; CLC1MD CLC1 enabled; CLC2MD CLC2 enabled; 
    PMD6 = 0x00;
    // DMA1MD DMA1 enabled; DMA2MD DMA2 enabled; 
    PMD7 = 0x00;
}

void OSCILLATOR_Initialize(void) //still need to set up
{
    OSCCON1bits.NDIV = 0x0; //Set oscillator divider to 1:1
    OSCCON1bits.NOSC = 0x7; //select external oscillator

    //wait until the clock switch has happened
    while (OSCCON3bits.ORDY == 0)  {}

    //if the currently active clock (CON2) isn't the selected clock (CON1)
    if (OSCCON2 != 0x70) {
        //Unhandled error (the oscillator isn't there). Fail fast, with an infinite loop.
        while (1) {}
    }

}


