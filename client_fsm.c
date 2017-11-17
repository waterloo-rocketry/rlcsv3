#include "client_fsm.h"
#include "shared_types.h"
#include "radio_comms.h"

//we need to receive ack requests, we need to receive state updates,
//and we need to receive daq updates. Those should be the only things
//clients receive

char buffer[DAQ_RADIO_LEN]; //the daq radio input should be the longest thing we get
unsigned short buffer_index = 0;
unsigned short data_len = 0;
enum {
    REC_NOTHING;
    REC_STATE;
    REC_DAQ;
    REC_ACK;
} state;

//returns 1 if data is a base 64 digit that's ok to come over the radio
int valid_data_byte(char data) {
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

void handle_state_update(char* buffer, actuator_state_t* state){
    //unpack buffer, copy values into state

}

void handle_daq_update(char* buffer, daq_holder_t* daq){
    //unpack buffer, copy values into daq

}

void handle_ack_request(char* buffer, actuator_state_t* state){
    //if the decoded state from buffer[0] is the same as state, then send an ack over the radio
    //if they aren't the same, send a nack

}

void push_radio_char(char input){
    switch (input) {
        case RADIO_STATE_HEADER:
            state = REC_STATE;
            buffer_index = 0;
            data_len = 1; //only one byte in a state update
            return;
        case RADIO_DAQ_HEADER:
            state = REC_DAQ;
            buffer_index = 0;
            data_len = DAQ_RADIO_LEN; //takes this many bytes for a daq update
            return;
        case RADIO_ACK_HEADER:
            state = REC_ACK;
            buffer_index = 0;
            data_len = 1; //only one byte in an ack request. It's a state byte
            return;
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
            handle_state_update(buffer, &tower_state);
            break;
        case REC_DAQ:
            handle_daq_update(buffer, &tower_daq);
            break;
        case REC_ACK:
            handle_ack_request(buffer, get_button_state());
            break;
        default:
            break;
    }

    //we've received a full command, we've processed a full command, go back to
    //the default state and reset the buffer index
    state = REC_NOTHING;
    buffer_index = 0;
}
