#include "client_fsm.h"
#include "shared_types.h"
#include "radio_comms.h"
#include "Arduino.h"
#include "sd_handler.h"
#include "client_globals.h"
#include "LCD.h"
#include "wrt_sdl.h"

//we need to receive ack requests, we need to receive state updates,
//and we need to receive daq updates. Those should be the only things
//clients receive

// Private variables
static wsdl_ctx_t state_ctx, daq_ctx;
daq_holder_t daq_recv;
actuator_state_t state_recv;


//returns 1 if data is a base 64 digit that's ok to come over the radio
static int valid_data_byte(char data)
{
    if (data >= 'A' && data <= 'Z')
        return 1;
    if (data >= 'a' && data <= 'z')
        return 1;
    if (data >= '0' && data <= '9')
        return 1;
    if (data == '+' || data == '/')
        return 1;
    return 0;
}

extern unsigned long global_time_last_tower_state_req;
static void handle_state_update(const actuator_state_t *new_state, actuator_state_t *old_state)
{
    //log the last received tower state
    if (sd_active()) {
        rlcslog_client_tower_state(new_state);
    }
    memcpy(old_state, new_state, sizeof(*old_state));
    global_time_last_tower_state_req = millis_offset();
}

extern unsigned long global_time_last_tower_daq_req;
static void handle_daq_update(const daq_holder_t *new_daq, daq_holder_t *old_daq)
{
    if (sd_active()) {
        rlcslog_log_daq_values(new_daq);
    }
    memcpy(old_daq, new_daq, sizeof(*old_daq));
    global_time_last_tower_daq_req = millis_offset();
}

void push_radio_char(char input)
{
    static enum {
        REC_NOTHING,
        REC_STATE,
        REC_DAQ,
        REC_ERROR,
    } state;

    switch (input) {
        case RADIO_STATE_REQ:
            state = REC_STATE;
            wsdl_begin_deserialization(&state_ctx, &state_recv, sizeof(state_recv));
            return;
        case RADIO_DAQ_REQ:
            state = REC_DAQ;
            wsdl_begin_deserialization(&daq_ctx, &daq_recv, sizeof(daq_recv));
            return;
        case '!':
            state = REC_ERROR;
            // TODO, deal with errors at some point
            break;
        default:
            break;
    }

    if (!valid_data_byte(input) || state == REC_NOTHING)
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
                handle_state_update(&state_recv, get_tower_state());
                state = REC_NOTHING;
            } else {
                // still going
            }
            break;
        case REC_DAQ:
            deserialize_result = wsdl_deserialize_byte(&daq_ctx, input);
            if (deserialize_result < 0) {
                // An error occurred
                state = REC_NOTHING;
            } else if (deserialize_result == 0) {
                // Deserialization finished
                handle_daq_update(&state_recv, get_tower_state());
                state = REC_NOTHING;
            } else {
                // still going
            }
            break;
        default:
            break;
    }
}
