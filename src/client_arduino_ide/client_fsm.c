#include "client_fsm.h"
#include "shared_types.h"
#include "radio_comms.h"
#include "Arduino.h"
#include "sd_handler.h"
#include "client_globals.h"
#include "LCD.h"

//we need to receive ack requests, we need to receive state updates,
//and we need to receive daq updates. Those should be the only things
//clients receive

static char buffer[50]; //the daq radio input should be the longest thing we get
static unsigned short buffer_index = 0;
static unsigned short data_len = 0;
enum {
    REC_NOTHING,
    REC_STATE,
    REC_DAQ,
    REC_ACK,
    REC_ERROR
} state;

//returns 1 if data is a base 64 digit that's ok to come over the radio
static int valid_data_byte(char data) {
    if(data >= 'A' && data <= 'Z')
        return 1;
    if(data >= 'a' && data <= 'z')
        return 1;
    if(data >= '0' && data <= '9')
        return 1;
    if(data == '+' || data == '/')
        return 1;
    return 0;
}

extern unsigned long global_time_last_tower_state_req;
static void handle_state_update(char* state_buffer, actuator_state_t* state){
    //log the last received tower state
    if(sd_active()){
        rlcslog_client_tower_state(state_buffer[0]);
    }
    //unpack buffer, copy values into state
    convert_radio_to_state(state,*state_buffer);
    global_time_last_tower_state_req = millis_offset();
}

extern unsigned long global_time_last_tower_daq_req;
static void handle_daq_update(char* buffer, daq_holder_t* daq){
    //unpack buffer, copy values into daq
    daq_radio_value_t s;
    for(int i = 0; i < DAQ_RADIO_LEN; i++){
        //check that all bytes are valid
        if(fromBase64(buffer[i]) < 0)
            return;
    }
    strncpy(s.data, buffer, DAQ_RADIO_LEN);
    rlcslog_log_daq_values(&s);
    convert_radio_to_daq(daq, &s);
    global_time_last_tower_daq_req = millis_offset();
}

static void handle_ack_request(char* buffer, actuator_state_t* state){
    //if the decoded state from buffer[0] is the same as state, then send an ack over the radio
    //if they aren't the same, send a nack
    actuator_state_t received;
    convert_radio_to_state(&received, *buffer);
    if(actuator_compare(state, &received)) {
        client_ack();
    }
    else{
        client_nack();
    }
}

void push_radio_char(char input){
    switch (input) {
        case RADIO_STATE_REQ:
            state = REC_STATE;
            buffer_index = 0;
            data_len = 1; //only one byte in a state update
            return;
        case RADIO_DAQ_REQ:
            state = REC_DAQ;
            buffer_index = 0;
            data_len = DAQ_RADIO_LEN; //takes this many bytes for a daq update
            return;
        case RADIO_ACK_BYTE:
            state = REC_ACK;
            buffer_index = 0;
            data_len = 1; //only one byte in an ack request. It's a state byte
            return;
        case '!':
            state = REC_ERROR;
            buffer_index = 0;
            data_len = 13;
            break;
        default:
            break;
    }
    if(!valid_data_byte(input) || state == REC_NOTHING)
        //we either received a byte that wansn't data, or we weren't expecting any data
        return;
    
    //at this point, we assume that we just want to push the input into the buffer. We will also assume
    //that this won't overflow. Maybe eventually put in a check that this won't overflow.
    buffer[buffer_index++] = input;

    //check if we're still waiting for more bytes in the current command. If so, return to wait for more
    if(buffer_index < data_len)
        return;

    //now we assume that we've received a full command, and it's stored in buffer starting at index 0.
    //so now we just call the appropriate handler
    switch(state){
        case REC_STATE:
            handle_state_update(buffer, get_tower_state());
            break;
        case REC_DAQ:
            handle_daq_update(buffer, get_tower_daq());
            break;
        case REC_ACK:
            handle_ack_request(buffer, get_button_state());
            break;
        case REC_ERROR:
            buffer[13] = 0;
            char error_to_display[21];
            error_to_display[0] = buffer[0];
            error_to_display[1] = buffer[1];
            error_to_display[2] = buffer[2];
            error_to_display[3] = ' ';
            error_to_display[4] = buffer[3];
            error_to_display[5] = buffer[4];
            error_to_display[6] = ' ';
            error_to_display[7] = buffer[5];
            error_to_display[8] = buffer[6];
            error_to_display[9] = ' ';
            error_to_display[10] = buffer[7];
            error_to_display[11] = buffer[8];
            error_to_display[12] = ' ';
            error_to_display[13] = buffer[9];
            error_to_display[14] = buffer[10];
            error_to_display[15] = ' ';
            error_to_display[16] = buffer[11];
            error_to_display[17] = buffer[12];
            error_to_display[18] = '\0';
            display_new_error(error_to_display);
        default:
            break;
    }

    //we've received a full command, we've processed a full command, go back to
    //the default state and reset the buffer index
    state = REC_NOTHING;
    buffer_index = 0;
}
