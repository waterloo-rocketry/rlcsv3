#include "nodeio.ioio.h"
#include "Arduino.h"

//packets that can be sent over the radio
//their meanings are better understood if
//read the giant switch statement in the
//refresh function
#define NIO_VENT_OPEN       '{'
#define NIO_VENT_CLOSE      '}'
#define NIO_INJ_OPEN        '['
#define NIO_INJ_CLOSE       ']'
#define NIO_ACK_HEADER      ':'
#define NIO_NACK_HEADER     ';'
#define NIO_SENSOR_HEADER   '?'


#ifndef NODE_GROUND
//stuff that only applies to the slaves (the injector and
//the vent section microcontrollers)

//it is assumed that both slaves use the primary Serial
//interface to talk to the xbee. Alex, if that isn't the
//case (if you're using software serial for some reason),
//here is where to change this
#define RADIO_UART Serial

//it is assumed that driving the valve is done with two
//wires. Setting the close wire high and the open wire
//high closes the valve, and vice versa (writing both
//wires high results in getting eaten by a velociraptor)
static int pin_close, pin_open;

//different states that the valve can be in. This is for
//writing, not reading. So this holds the "desired" valve
//state, reading the limit switches is what tells you the
//actual state of the valve
enum actuator_state{
    NOTHING,
    VALVE_OPEN,
    VALVE_CLOSED
};
//default states for maximum safety.
#ifdef NODE_VENT
//if the rocket doesn't know what to do, it should _open_ the vent valve
actuator_state current_state = VALVE_OPEN;
#elif defined(NODE_INJ)
//there's no good default here. If the system resets during launch,
//we need the valve open. if it resets during fill, that valve needs
//to be closed. So just do nothing at startup
actuator_state current_state = NOTHING;
#endif //ifdef NODE_VENT
//if these two states are different, the slave will be constantly
//requesting an acknowledgement. So setting them equal at startup
//stops them from crowding the bandwidth
actuator_state current_requested_state = current_state;

//helper functions
void apply_state(actuator_state s);
void slave_request_ack(actuator_state s);

#else
//stuff that only applies to master, in this case RLCS tower side
//it currently uses the Serial1 interface
#define RADIO_UART Serial1
#endif //ifndef NODE_GROUND


//init function. Called at startup
void nio_init(int pin_valve_close, int pin_valve_open){
    //Alex, this blocks at startup if there is no
    //serial interface connected. This seems safest,
    //if the slaves don't have a radio, they really
    //shouldn't be doing anything
    while(!RADIO_UART);
    //make sure to set the radio module to 9600 baud.
    RADIO_UART.begin(9600);
#ifndef NODE_GROUND
    //things that the slaves do and master doesn't
    pin_close = pin_valve_close;
    pin_open = pin_valve_open;
    pinMode(pin_close, OUTPUT);
    pinMode(pin_open, OUTPUT);
    apply_state(current_state);
#endif
}

//different states the FSM can be in
enum nio_states{
    STATE_NONE,
    STATE_ACK_RECEIVE,
    STATE_SENSOR_RECEIVE
};

nio_states current_fsm_state = STATE_NONE;
void nio_refresh(){
//implement a fsm. This is largely based off the one used by RLCS.
//This isn't done atm (only works for vent slave). The explanatory
//comments will be updated when this function actually does stuff
    if(RADIO_UART.available()){
        char x = RADIO_UART.read();
        switch(x){
            case NIO_VENT_OPEN:
#ifdef NODE_GROUND
                //this should only happen if the vent slave is requesting an ack
#elif defined(NODE_VENT)
                if(current_fsm_state == STATE_ACK_RECEIVE){
                    //we asked them to ack this, and they are
                    if(current_requested_state == VALVE_OPEN){
                        apply_state(VALVE_OPEN);
                    } else {
                        //WHAT THE FLYING FUCK
                        //they requested a state, we replied with an ack request,
                        //and they replied with an ack _for the other state_.
                        //I guess we just treat this as a nack
                        current_requested_state = current_state;
                    }
                    current_fsm_state = STATE_NONE;
                } else {
                    //we need to request acknowledgement of this packet
                    //that's done outside this switch.
                    current_requested_state = VALVE_OPEN;
                }
#endif
                break;
            case NIO_VENT_CLOSE:
#ifdef NODE_GROUND
#elif defined(NODE_VENT)
                //this code is identical to the code for valve open,
                //just... you know... for closing
                if(current_fsm_state == STATE_ACK_RECEIVE){
                    if(current_requested_state == VALVE_CLOSED){
                        apply_state(VALVE_CLOSED);
                    } else {
                        current_requested_state = current_state;
                    }
                    current_fsm_state = STATE_NONE;
                } else {
                    current_requested_state = VALVE_CLOSED;
                }
#endif
                break;
            case NIO_INJ_OPEN:
                break;
            case NIO_INJ_CLOSE:
                break;
            case NIO_ACK_HEADER:
#ifdef NODE_GROUND
#elif defined(NODE_VENT)
                current_fsm_state = STATE_ACK_RECEIVE;
#endif
                break;
            case NIO_NACK_HEADER:
#if defined(NODE_VENT) || defined(NODE_INJ)
                current_fsm_state = STATE_NONE;
                current_requested_state = current_state;
#endif
                break;
            case NIO_SENSOR_HEADER:
                //we'll deal with this later
                current_fsm_state = STATE_SENSOR_RECEIVE;
                break;
            default:
                break;
        }
        if(current_fsm_state == STATE_SENSOR_RECEIVE){
#ifdef NODE_GROUND
            //we have received a sensor update
#endif
        }
    }
    //now some housekeeping
    //if we need to request an ACK, request an ACK.
    if(current_requested_state != current_state){
        //this function handles its own time handling
        //otherwise we'd be sending packets as fast
        //as humanly (avr-ly) possible. Which is bad.
        slave_request_ack(current_requested_state);
    }
}

//using rfc 4648 base 64. Yes there's probably a library for this.
//these are used for converting sensor data into radio packets (and
//converting them back). They're currently not used since the sensor
//data conversion isn't actually written.
char fromBase64(char base64){
    if ( base64 >= 'A' && base64 <= 'Z' ) {
        //we need to map 'A' (ascii value 65) to 0. So subtract 65
        base64 -= 65;
    } else if (base64 >= 'a' && base64 <= 'z') {
        //we need to map 'a' (ascii value 97) to 26. So subtract 71
        base64 -= 71;
    } else if (base64 >= '0' && base64 <= '9') {
        //we need to map '0' (ascii value 48) to 52. So add 4
        base64 += 4;
    } else if (base64 == '+') {
        //we need to map '+' (ascii value 43) to 62. So add 19
        base64 += 19;
    } else if (base64 == '/') {
        //we need to map '/' (ascii value 47) to 63. so add 16
        base64 += 16;
    } else {
        //we have failed. So return -1
        return -1;
    }
    return base64;
}
char toBase64(char binary){
    if (binary >= 0 && binary <= 25) {
        //map to 'A' (ascii value 65). So add 65
        binary += 65;
    } else if (binary >= 26 && binary <= 51) {
        //map to 'a' (ascii value 97). So add 71
        binary += 71;
    } else if (binary >= 52 && binary <= 61) {
        //map to '0' (ascii value 48). So subtract 4
        binary -= 4;
    } else if (binary == 62) {
        //map to '+' (ascii value 43). So subtract 19
        binary -= 19;
    } else if (binary == 63) {
        //map to '/' (ascii value 47). So subtract 16
        binary -= 16;
    } else {
        //we have failed. So return -1
        return -1;
    }
    return binary;
}

//returns 1 on success. If it doesn't return 1, then
//we for some reason couldn't generate a proper output
//radio string, so don't send output.
int pack_sensor_data(char *output, sensor_data_t* data){
    //we're packing this into a base 64 character string,
    //so we have 6 bits per character to play with
    //shove ID information, the two limit switches, and first 3 bits
    //of pressure into the first char
    char temp;
#ifdef NODE_INJ
    //injector section puts a 0 in leading bit
    temp = 0;
#endif
#ifdef NODE_VENT
    //vent valve puts a 1 in the leading bit
    temp = 0b100000;
#endif
    //valve limitswitch open gets the 4th bit
    temp |= ((data->valve_limitswitch_open != 0) << 4);
    //valve limitswitch closed gets 3rd bit
    temp |= ((data->valve_limitswitch_closed != 0) << 3);
    //top three bits of pressure value into temp
    uint16_t pressure_holder = data->pressure;
    //turn pressure into a 9 bit number by left shiting and
    //taking only those 9 bits (if it was more than a 10 bit number,
    //how the hell did you get so much precision out of a 10bit adc?)
    pressure_holder = ((pressure_holder >> 1) & 0x1FF);
    temp |= ((pressure_holder >> 6) & 0b111);
    //convert temp to base 64, pu into first char of output
    *output = toBase64(temp);
    
    //put bottom 6 bits of pressure into output[1]
    output[1] = toBase64(pressure_holder & 0x3F);

    //TODO, if we want thermistors, that'll have to go here

    return 1;
}

//returns 1 on success. This function doesn't do anything,
//so please don't call it
int unpack_sensor_data(char *input, sensor_data_t* output){
    //take first byte of input, convert from Base 64,
    //and 

    //TODO, fix this
    return 4;
}

//TODO, this
void nio_send_sensor_data(sensor_data_t* data){
}

//returns 1 if open, 0 if other.
//this returns 0 if we're in the "nothing"
//state, so be advised of that
uint8_t nio_current_valve_state(){
    //this is based on the last received
    //tower command. THIS MIGHT NOT REFLECT
    //WHAT THE VALVE IS ACTUALLY DOING. For
    //the actual state, check the limit switches
    return current_state == VALVE_OPEN;
}

//write the output pins. update the current_state variable.
void apply_state(actuator_state s){
    if(s == VALVE_OPEN){
        //write high to the "open pin", and low to the "close" pin
        digitalWrite(pin_close, LOW);
        digitalWrite(pin_open, HIGH);
    } else if(s == VALVE_CLOSED){
        //the opposite of that one
        digitalWrite(pin_open, LOW);
        digitalWrite(pin_close, HIGH);
    } else {
        //write them both low. TODO alex confirm that this is how
        //to power off your h-bridge thing
        digitalWrite(pin_close, LOW);
        digitalWrite(pin_open,  LOW);
    }
    current_state = s;
}

unsigned long time_last_ack_sent = 0;
//send, at max, one ack request every 500 milliseconds
const unsigned long min_time_between_acks = 500;
void slave_request_ack(actuator_state s){
    if((millis() - time_last_ack_sent) < min_time_between_acks)
        //don't spam the channel
        return;
    if(s == VALVE_OPEN) {
        RADIO_UART.write(NIO_ACK_HEADER);
#ifdef NODE_VENT
        RADIO_UART.write(NIO_VENT_OPEN);
#elif defined(NODE_INJ)
        RADIO_UART.write(NIO_INJ_OPEN);
#endif
        time_last_ack_sent = millis();
    } else if (s == VALVE_CLOSED) {
        RADIO_UART.write(NIO_ACK_HEADER);
#ifdef NODE_VENT
        RADIO_UART.write(NIO_VENT_CLOSE);
#elif defined(NODE_INJ)
        RADIO_UART.write(NIO_INJ_CLOSE);
#endif
        time_last_ack_sent = millis();
    }
}
