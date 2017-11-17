#ifndef RADIO_COMMS_H_
#define RADIO_COMMS_H_

#ifdef __cplusplus
//extern "C" {
#endif

#include "shared_types.h"

//we can't use any letters or numbers or + or / as header bytes,
//since they're used for base64
//are these gonna be legible? No. Probably not. Sorry.
#define RADIO_ACK_BYTE '['
#define RADIO_NACK_BYTE ']'
#define RADIO_STATE_REQ '{'
#define RADIO_DAQ_REQ '}'
#define RADIO_STATE_ASSIGN ';'

//return 1 on success, 0 on failure (serial overrun, or sending before timeout)
int client_request_state();
int client_request_daq();
int client_push_state(actuator_state_t* state);
int client_ack();
int client_nack();

int tower_request_ack(actuator_state_t* state);
int tower_send_state(actuator_state_t* state);
int tower_send_daq(daq_holder_t* daq);

#ifdef __cplusplus
//}
#endif

#endif //ifndef RADIO_COMMS_H_
