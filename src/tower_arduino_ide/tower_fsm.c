#include "tower_fsm.h"
#include "shared_types.h"
#include "radio_comms.h"
#include "tower_globals.h"
#include "Arduino.h"
#include "serialization_lib/wrt_sdl.h"
#include "tower_pin_defines.h"

//we need to receive state_commands. Those should be the only things
//the tower receives

// Private variables
static wsdl_ctx_t state_ctx;
actuator_state_t state_recv;

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

static void handle_state_command(const actuator_state_t* recvd_state){
    actuator_state_t *req_state = get_requested_state();
    *req_state = *recvd_state;
    if(digitalRead(PIN_KEY_SWITCH_INPUT)) {
        apply_state();
    }
}

extern unsigned long time_last_contact;

void push_radio_char(char input){
    static enum {
        REC_NOTHING,
        REC_STATE
    } state;

    switch (input) {
		case RADIO_STATE_ASSIGN:
            time_last_contact = millis_offset();
			state = REC_STATE;
            wsdl_begin_deserialization(&state_ctx, (uint8_t*) &state_recv, sizeof(state_recv));
			return;
        case RADIO_STATE_REQ:
            time_last_contact = millis_offset();
            tower_send_state(get_current_state());
            return;
        case RADIO_DAQ_REQ:
            tower_send_daq(get_global_current_daq());
            return;
        default:
            break;
    }
    if(!valid_data_byte(input) || state == REC_NOTHING)
        //we either received a byte that wansn't data, or we weren't expecting any data
        return;
    
    int deserialize_result;
    switch (state) {
        case REC_STATE:
            deserialize_result = wsdl_deserialize_byte(&state_ctx, input);
            if (deserialize_result < 0) {
                // An error occurred
                state = REC_NOTHING;
            } else if (deserialize_result == 0) {
                // Deserialization finished
                handle_state_command(&state_recv);
                state = REC_NOTHING;
            } else {
                // still going
            }
            break;
    }
}
