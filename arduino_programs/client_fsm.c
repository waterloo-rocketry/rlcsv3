#include "client_fsm.h"
#include "shared_types.h"
#include "radio_comms.h"
#include "Arduino.h"
#include "client_globals.h"

//we need to receive ack requests, we need to receive state updates,
//and we need to receive daq updates. Those should be the only things
//clients receive

char buffer[DAQ_RADIO_LEN]; //the daq radio input should be the longest thing we get
unsigned short buffer_index = 0;
unsigned short data_len = 0;
enum {
    REC_NOTHING,
    REC_STATE,
    REC_DAQ,
    REC_ACK
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

extern unsigned long global_time_last_tower_state_req;
void handle_state_update(char* buffer, actuator_state_t* state){
    //unpack buffer, copy values into state
    convert_radio_to_state(state,*buffer);
    global_time_last_tower_state_req = millis_offset();
}

extern unsigned long global_time_last_tower_daq_req;
void handle_daq_update(char* buffer, daq_holder_t* daq){
    //unpack buffer, copy values into daq
    global_time_last_tower_daq_req = millis_offset();
}

void handle_ack_request(char* buffer, actuator_state_t* state){
    //if the decoded state from buffer[0] is the same as state, then send an ack over the radio
    //if they aren't the same, send a nack
    actuator_state_t received;
    convert_radio_to_state(&received, *buffer);
#ifdef RLCS_DEBUG
    radio_println("");
    radio_print("received byte ");
    radio_print_char(*buffer);
    radio_println("");
    char temp;
    convert_state_to_radio(state, &temp);
    radio_print("current byte ");
    radio_print_char(temp);
    radio_println("");
    radio_print("received: ");
    radio_println(received.remote_fill_valve ? "remote_fill_valve open" : "remote_fill_valve closed");
    radio_println(received.remote_vent_valve ? "remote_vent_valve open" : "remote_vent_valve closed");
    radio_println(received.run_tank_valve ? "run_tank_valve open" : "run_tank_valve closed");
    radio_println(received.injector_valve ? "injector_valve open" : "injector_valve closed");
    radio_println(received.linear_actuator ? "linear_actuator open" : "linear_actuator closed");
    radio_println(received.ignition_power ? "ignition_power open" : "ignition_power closed");
    radio_println(received.ignition_select ? "ignition_select open" : "ignition_select closed");
    radio_print("button: ");
    radio_println(state->remote_fill_valve ? "remote_fill_valve open" : "remote_fill_valve closed");
    radio_println(state->remote_vent_valve ? "remote_vent_valve open" : "remote_vent_valve closed");
    radio_println(state->run_tank_valve ? "run_tank_valve open" : "run_tank_valve closed");
    radio_println(state->injector_valve ? "injector_valve open" : "injector_valve closed");
    radio_println(state->linear_actuator ? "linear_actuator open" : "linear_actuator closed");
    radio_println(state->ignition_power ? "ignition_power open" : "ignition_power closed");
    radio_println(state->ignition_select ? "ignition_select open" : "ignition_select closed");

    //now a full comparison
    radio_println(state->remote_fill_valve == received.remote_fill_valve ? "remote_fill_valve matches" : "remote_fill_valve doesn't match");
    radio_println(state->remote_vent_valve == received.remote_vent_valve ? "remote_vent_valve matches" : "remote_vent_valve doesn't match");
    radio_println(state->run_tank_valve == received.run_tank_valve ? "run_tank_valve matches" : "run_tank_valve doesn't match");
    radio_println(state->linear_actuator == received.linear_actuator ? "linear_actuator matches" : "linear_actuator doesn't match");
    radio_println(state->ignition_power == received.ignition_power ? "ignition_power matches" : "ignition_power doesn't match");
    radio_println(state->ignition_select == received.ignition_select ? "ignition_select matches" : "ignition_select doesn't match");

    radio_println("");
    radio_print("button remote_vent_valve: ");
    radio_print_char(state->remote_vent_valve + '0');
    radio_print(", received remote_vent_valve: ");
    radio_print_char(received.remote_vent_valve + '0');
    radio_println("");
#endif
    if(actuator_compare(state, &received)) {
#ifdef RLCS_DEBUG
        radio_println("they match");
#endif
        client_ack();
    }
    else{
#ifdef RLCS_DEBUG
        radio_println("they don't match");
#endif
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
#ifdef RLCS_DEBUG
        case '!':
            radio_println("");
            radio_print("button: ");
            radio_println(get_button_state()->remote_fill_valve ? "remote_fill_valve open" : "remote_fill_valve closed");
            radio_println(get_button_state()->remote_vent_valve ? "remote_vent_valve open" : "remote_vent_valve closed");
            radio_println(get_button_state()->run_tank_valve ? "run_tank_valve open" : "run_tank_valve closed");
            radio_println(get_button_state()->injector_valve ? "injector_valve open" : "injector_valve closed");
            radio_println(get_button_state()->linear_actuator ? "linear_actuator open" : "linear_actuator closed");
            radio_println(get_button_state()->ignition_power ? "ignition_power open" : "ignition_power closed");
            radio_println(get_button_state()->ignition_select ? "ignition_select open" : "ignition_select closed");
            break;
#endif
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
        default:
            break;
    }

    //we've received a full command, we've processed a full command, go back to
    //the default state and reset the buffer index
    state = REC_NOTHING;
    buffer_index = 0;
}
