#include <xc.h>
#include <stdio.h>
#include <stdlib.h>

#include "system_init.h"
#include "pin_manager.h"
#include "timer.h"

#include "canlib/can.h"
#include "canlib/can_common.h"
#include "canlib/pic18f26k83/pic18f26k83_can.h"
#include "canlib/message_types.h"
#include "canlib/util/timing_util.h"
#include "canlib/util/can_tx_buffer.h"

#include "i2c.h"

#define _XTAL_FREQ 12000000
#define MAX_LOOP_TIME_DIFF_ms 250


//memory pool for the CAN tx buffer
uint8_t tx_pool[100];

static void send_status_ok(void);
void can_msg_handler(const can_msg_t *msg);


void main(void) {
    
    SYSTEM_Initialize(); // calls oscillator init, pin manager init and PMD init
    // need to edit pragmas in device config
    timer0_init();
    i2c_slave_init();
    
    // Enable global interrupts
    INTCON0bits.GIE = 1;

    // Set up CAN TX
    TRISC1 = 0;
    RC1PPS = 0x33;

    // Set up CAN RX
    TRISC0 = 1;
    ANSELC0 = 0;
    CANRXPPS = 0x10;
    
   
      // set up CAN module
    can_timing_t can_setup;
    can_generate_timing_params(_XTAL_FREQ, &can_setup);
    can_init(&can_setup, can_msg_handler);
    // set up CAN tx buffer
    txb_init(tx_pool, sizeof(tx_pool), can_send, can_send_rdy);

    // loop timer
    uint32_t last_millis = millis();
    
    while (1){ // main event loop
        
        if (millis() - last_millis > MAX_LOOP_TIME_DIFF_ms) {
            //send_status_ok();
            last_millis = millis();
        }
        
        txb_heartbeat();  
       
    }
   
}

static void __interrupt() interrupt_handler() {
    
    if (PIR5) {
        can_handle_interrupt();
    }
    
    if (PIR3bits.I2C1IF == 1){
        i2c_handle_interrupt();
    }
    
    if (PIR3bits.I2C1EIF == 1){
        i2c_handle_interrupt();
    }
    
    if (PIR2bits.I2C1RXIF == 1){
        i2c_handle_interrupt();
    }
    
    if (PIR3bits.I2C1TXIF == 1){
        i2c_handle_interrupt();
    }
    
   
    
   

    // Timer0 has overflowed - update millis() function
    // This happens approximately every 500us
    if (PIE3bits.TMR0IE == 1 && PIR3bits.TMR0IF == 1) {
        timer0_handle_interrupt();
        PIR3bits.TMR0IF = 0;
    }
}

static void send_status_ok(void) {
    can_msg_t board_stat_msg;
    build_board_stat_msg(millis(), E_NOMINAL, NULL, 0, &board_stat_msg);

    // send it off at low priority
    txb_enqueue(&board_stat_msg);
}

void can_msg_handler(const can_msg_t *msg) {
    uint16_t msg_type = get_message_type(msg);

    // ignore messages that were sent from this board
    if (get_board_unique_id(msg) == BOARD_UNIQUE_ID) {
        
        return;
    }

    // declare this in advance cause we can't declare it inside the switch
    uint8_t alt_num = 0;
    enum ARM_STATE desired_arm_state = ARMED;
    int dest_id; // the destination board id for reset

    switch (msg_type) {
        case MSG_ALT_ARM_CMD:
           // get_req_arm_state(msg, &alt_num, &desired_arm_state);
           // if(alt_num == 1) { alt_1_arm_state = desired_arm_state; }
           // if(alt_num == 2) { alt_2_arm_state = desired_arm_state; }
            break;

        case MSG_LEDS_ON:
//            RED_LED_ON();
//            BLUE_LED_ON();
//            WHITE_LED_ON();
            break;

        case MSG_LEDS_OFF:
//            RED_LED_OFF();
//            BLUE_LED_OFF();
//            WHITE_LED_OFF();
            break;
            
        case MSG_RESET_CMD:
            dest_id = get_reset_board_id(msg);
            if(dest_id == BOARD_UNIQUE_ID || dest_id == 0 ) { RESET(); }
            break;

        default:
            // this is where we go for all the messages we don't care about
            break;
    }
}