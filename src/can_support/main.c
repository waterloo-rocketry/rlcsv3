#include <xc.h>
#include "timer.h"


void main(void) {
    SYSTEM_Initialize(); // copy and paste and put in own code. Edit
    OSCILLATOR_Initialize();
    FVR_Initialize();

    ADCC_Initialize();
    ADCC_DisableContinuousConversion();
    
    // Enable global interrupts
    
    INTCON0bits.GIE = 1;

    // Set up CAN TX
    TRISC1 = 0;
    RC0PPS = 0x33; // ?

     // Set up CAN RX
    TRISC0 = 1;
    ANSELC0 = 0;
    CANRXPPS = 0x11; // ? 

    // local initializers
    timer0_init();
    
    // set up CAN module
    can_timing_t can_setup;
    can_generate_timing_params(_XTAL_FREQ, &can_setup);

    can_init(&can_setup, can_msg_handler);
    // set up CAN tx buffer
    txb_init(tx_pool, sizeof(tx_pool), can_send, can_send_rdy);

    uint32_t last_millis = millis();
    
    // Any custom functions that need to be set up
    // where to include i2c stuff?
    
     while (1) {

        // Check status, messages, valve requests every MAX_LOOP_TIME_DIFF_ms millis
        // Avoid spamming bus traffic and sending too many extra valve commands
        if (millis() - last_millis > MAX_LOOP_TIME_DIFF_ms) {

            bool status_ok = true;
            // force all the checks to be performed
            status_ok &= check_battery_voltage_error();
            status_ok &= check_bus_current_error();
            status_ok &= check_valve_pin_error(requested_valve_state);
            //check all possible error messages

            if (status_ok) {
                send_status_ok();
            }
   
    
    
   
}
