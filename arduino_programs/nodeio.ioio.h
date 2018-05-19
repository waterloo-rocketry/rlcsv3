#ifndef NODEIO_IOIO_H
#define NODEIO_IOIO_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

/* Nodeio.ioio is the name of the local area network formed by three xbees
 * on or around the rocket, one being in the injector valve section (which
 * is named inj), one in the vent section (which is named vent), and one in
 * the tower side RLCS box (which is named ground).
 *
 * Nodeio.ioio has three goals:
 *  - Open the injector valve when the operator says so
 *  - Open the vent valve when the operator says so
 *  - send sensor data from both inj and vent back to the operator
 *
 * The sensor data is held in a sensor_data_t. Leave values unchanged if they
 * aren't needed, send them with nodeioio_send_sensor_data as often as you want.
 *
 * All actuator control is handled in nodeio_ioio_refresh. It currently assumes 
 * that the valve is closed by setting pin pin_valve_closed high and the other
 * pin low (is that as desired?). Set this up by passing the pin numbers to the
 * init function at program startup.
 */

#define NUM_THERMISTORS 4
#define SENSOR_DATA_LENGTH (2+(NUM_THERMISTORS))
typedef struct{
    uint16_t pressure;
    uint8_t valve_limitswitch_open;
    uint8_t valve_limitswitch_closed;
    uint8_t thermistor_data[NUM_THERMISTORS];
} sensor_data_t;

//different states that the valve can be in. This is for
//writing, not reading. So this holds the "desired" valve
//state, reading the limit switches is what tells you the
//actual state of the valve
enum nio_actuator_state{
    NOTHING,
    VALVE_OPEN,
    VALVE_CLOSED
};

//amount of time between driving unused mosfets low and used mosfets high
//this is what for not shorting 50 amps through your board
#define MOSFET_SWITCH_TIME_MS 150
//initialization function. Sets up Serial communication, and actuator pins
void nio_init(int pin_valve_closed, int pin_valve_opened);

//call this function every loop. It checks for new packets, and handles
//incoming commands if need be (opening and closing the valve as needed)
void nio_refresh();

//call this function as often as is desired. It will send the sensor data
//back to the ground station, and through there to the operator
//Please call this at least every three seconds or so (faster is better)
//(but not like, every loop or anything).
void nio_send_sensor_data(sensor_data_t*);

//returns true if valve is open, false otherwise. This way you can log
//when the valve opens or closes. This is based off desired state, not
//the actual valve state. Read your limit switches for that
uint8_t nio_current_valve_state();

//compile guards, you need to compile this with either NODE_INJ, NODE_VENT,
//or NODE_GROUND defined (and only one of these). This changes how different
//functions are defined

#ifndef NODE_TEST //test file gets special treatment
//Yes, I know it's ugly. Yes, there's probably a better way. No, I'm
//not changing it.
#if !defined(NODE_INJ) && !defined(NODE_VENT) && !defined(NODE_GROUND)
#error "No node designator (NODE_{INJ,VENT,GROUND}) defined!"
#endif

#ifdef NODE_INJ
#ifdef NODEIO_IOIO_DESIGNATOR
#error "Multiple node designators (NODE_{INJ,VENT|GROUND}) defined!"
#endif
#define NODEIO_IOIO_DESIGNATOR
#endif

#ifdef NODE_VENT
#ifdef NODEIO_IOIO_DESIGNATOR
#error "Multiple node designators (NODE_{VENT,INJ|GROUND}) defined!"
#endif
#define NODEIO_IOIO_DESIGNATOR
#endif

#ifdef NODE_GROUND
#ifdef NODEIO_IOIO_DESIGNATOR
#error "Multiple node designators (NODE_{GROUND,VENT|INJ}) defined!"
#endif
#define NODEIO_IOIO_DESIGNATOR
#endif

#else
//need to delcare these here so they're generated as c symbols,
//not c++ symbols. Only matters while testing
int pack_sensor_data(char *,sensor_data_t*);
int unpack_sensor_data(char*, sensor_data_t*);
#endif //ifndef NODE_TEST

#ifdef __cplusplus
}
#endif

#endif
