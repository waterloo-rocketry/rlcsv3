#include "radio_comms.h"
#include "Arduino.h"

void write_to_xbee(char out)
{
    Serial.write(out);
}

int xbee_bytes_available()
{
    return Serial.available();
}

char xbee_get_byte()
{
    return Serial.read();
}

//maximimum rate of state requests is twice every second
unsigned long time_last_state_req_sent = 0;
const unsigned long millis_between_state_req = 500;
int client_request_state()
{
    if (millis() - time_last_state_req_sent < millis_between_state_req)
        //called too soon, don't saturate xbee
        return 0;
    write_to_xbee(RADIO_STATE_REQ);
    time_last_state_req_sent = millis();
    return 1;
}

//don't request daq updates more often than every second
unsigned long time_last_daq_req_sent = 0;
const unsigned long millis_between_daq_req = 1000;
int client_request_daq()
{
    if (millis() - time_last_daq_req_sent < millis_between_daq_req) 
        //called too soon, so don't send anything
        return 0;
    write_to_xbee(RADIO_DAQ_REQ);
    time_last_daq_req_sent = millis();
    return 1;
}

//don't push state more than twice every second
unsigned long time_last_state_push_sent = 0;
const unsigned long millis_between_state_push = 500;
int client_push_state(actuator_state_t* state)
{
    if (millis() - time_last_state_push_sent < millis_between_state_push) 
        //called too soon, so don't send anything
        return 0;
    time_last_state_push_sent = millis();
    char binary;
    if (!convert_state_to_radio(state, &binary))
        return 0;
    write_to_xbee(RADIO_STATE_ASSIGN);
    write_to_xbee(binary);
    return 1;
}

//don't send acknowledgements more than twice per second
unsigned long time_last_client_ack_sent = 0;
const unsigned long millis_between_client_ack = 500;
int client_ack()
{
    if (millis() - time_last_client_ack_sent < millis_between_client_ack)
        return 0;
    write_to_xbee(RADIO_ACK_BYTE);
    time_last_client_ack_sent = millis();
    return 1;
}

//don't send nacknowledgements more than twice per second
unsigned long time_last_client_nack_sent = 0;
const unsigned long millis_between_client_nack = 500;
int client_nack()
{
    if (millis() - time_last_client_nack_sent < millis_between_client_nack)
        return 0;
    write_to_xbee(RADIO_NACK_BYTE);
    time_last_client_nack_sent = millis();
    return 1;
}



//now for the tower side radio sending functions

unsigned long time_last_tower_ack_req = 0;
const unsigned long millis_between_tower_ack_req = 500;
int tower_request_ack(actuator_state_t* state)
{
    if (millis() - time_last_tower_ack_req < millis_between_tower_ack_req)
        return 0;
    char binary;
    if (!convert_state_to_radio(state, &binary))
        return 0;
    write_to_xbee(RADIO_ACK_BYTE);
    write_to_xbee(binary);
    time_last_tower_ack_req = millis();
    return 1;
}

unsigned long time_last_tower_send_state = 0;
const unsigned long millis_between_tower_send_state = 500;
int tower_send_state(actuator_state_t* state)
{
    if (millis() - time_last_tower_send_state < millis_between_tower_send_state)
        return 0;
    char binary;
    if (!convert_state_to_radio(state, &binary))
        return 0;
    write_to_xbee(RADIO_STATE_REQ);
    write_to_xbee(binary);
    time_last_tower_send_state = millis();
    return 1;
}

unsigned long time_last_tower_send_daq = 0;
const unsigned long millis_between_tower_send_daq = 1000;
int tower_send_daq(daq_holder_t* daq)
{
    if (millis() - time_last_tower_send_daq < millis_between_tower_send_daq)
        return 0;
    daq_radio_value_t output;
    if (!convert_daq_to_radio(daq, &output))
        return 0;
    write_to_xbee(RADIO_DAQ_REQ);
    for (int i = 0; i < DAQ_RADIO_LEN; i++)
        write_to_xbee(output.data[i]);
    time_last_tower_send_daq = millis();
    return 1;
}

