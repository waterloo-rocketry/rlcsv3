#include "tower_pin_defines.h"
#include "tower_fsm.h"
#include "tower_globals.h"
#include "radio_comms.h"
#include "shared_types.h"
#include "Arduino.h"

void setup() {
    //initialize all outputs
    init_outputs();
    Serial.begin(9600);
}

unsigned long time_last_contact = 0;
//goto safe mode after 5 seconds of radio silence
const unsigned long global_min_time_between_contacts = 5000;

void loop() {
    //check for inputs from radio
    while(Serial.available()){
        //update FSM, which will deal with command processing
        push_radio_char(Serial.read());
    }
    //get all the daq updates
    //this here's a TODO
    
    //check time last contact
    if (millis() - time_last_contact > global_min_time_between_contacts) {
        //goto safe mode
        //this here's another TODO
    }

    //if the requested state and the current state aren't the same,
    //then request an acknowledgement for 
    if(!actuator_compare(get_requested_state(), get_current_state()))
        tower_request_ack(get_requested_state());

    delay(100);
}
