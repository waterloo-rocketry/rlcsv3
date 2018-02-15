#include "tower_fsm.h"
#include "shared_types.h"
#include "radio_comms.h"
#include "tower_globals.h"
#include "Arduino.h"

//we need to receive state_commands, we need to receive daq_commands,
//and we need to receive acknowledgements. Those should be the only things
//the tower receives

//all commands that the tower receives have at most one 
enum {
    REC_NOTHING,
    REC_STATE,
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

void handle_state_command(char buffer, actuator_state_t* state){
    //decode buffer, copy values into state. The Ack requesting is handled in the main loop
    convert_radio_to_state(state, buffer);
}

void push_radio_char(char input){
    switch (input) {
		case RADIO_STATE_ASSIGN:
			state = REC_STATE;
			return;
        case RADIO_STATE_REQ:
            tower_send_state(get_current_state());
            return;
        case RADIO_DAQ_REQ:
            tower_send_daq(get_global_current_daq());
            return;
        case RADIO_ACK_BYTE:
            //copy the value from requested state to held state,
            //then make the actuators do the things requested of them in held state
			apply_state();
            return;
		case RADIO_NACK_BYTE:
			reset_request();
			return;
#ifdef RLCS_DEBUG
        case '!':
            radio_println("");
            radio_print("button: ");
            radio_println(get_current_state()->remote_fill_valve ? "remote_fill_valve open" : "remote_fill_valve closed");
            radio_println(get_current_state()->remote_vent_valve ? "remote_vent_valve open" : "remote_vent_valve closed");
            radio_println(get_current_state()->run_tank_valve ? "run_tank_valve open" : "run_tank_valve closed");
            radio_println(get_current_state()->injector_valve ? "injector_valve open" : "injector_valve closed");
            radio_println(get_current_state()->linear_actuator ? "linear_actuator open" : "linear_actuator closed");
            radio_println(get_current_state()->ignition_power ? "ignition_power open" : "ignition_power closed");
            radio_println(get_current_state()->ignition_select ? "ignition_select open" : "ignition_select closed");
            break;
#endif
        default:
            break;
    }
    if(!valid_data_byte(input) || state == REC_NOTHING)
        //we either received a byte that wansn't data, or we weren't expecting any data
        return;
    
    //at this point, we assume that we have received a state command, and that the state it
    //wants us to become is held in the char input. We should really put in asserts for all 
    //these assumptions that we're making
    handle_state_command(input, get_requested_state());

    //we've received a full command, we've processed a full command, go back to
    //the default state and reset the buffer index
    state = REC_NOTHING;
}
