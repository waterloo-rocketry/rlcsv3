#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#include "nodeio.ioio.h"

int randomSensorCompare(void);

int main(int argc, char* argv[]){
    srand(time(NULL));
    if(randomSensorCompare()){
        printf("Error on test randomSensorCompare(), bailing\n");
        exit(1);
    }
    printf("test %s passed successfully\n", argv[0]);
    exit(0);
}

void generateRandomSensorState(sensor_data_t* s){
    s->pressure = (rand() & 0x3FE); //10 bit number with 0 in last bit
    s->valve_limitswitch_open = rand() & 1;
    s->valve_limitswitch_closed = rand() & 1;
    for(int i = 0; i < NUM_THERMISTORS; i++)
        //10 bit number with the last 4 being 0's
        s->thermistor_data[i] = (rand() & 0x3F0);
}

int unpack_sensor_data(char *, sensor_data_t*);
int pack_sensor_data(char*, sensor_data_t*);
int randomSensorCompare(){
    sensor_data_t s;
    sensor_data_t q;
    //we randomly select a node, if this is 1 it's vent,
    //otherwise we selected injector
    int node = 0;
    //this is the node that unpack_sensor_data returned
    int other_node;
    char c[SENSOR_DATA_LENGTH];
    for(int i = 0; i < 100000; i++){
        generateRandomSensorState(&s);
        if(!(node = pack_sensor_data(c, &s))){
            printf("failure in pack_sensor_data\n");
            return 1;
        }
        if(node == 1){
            //we generated a vent sensor packet. So test that
            if(!(other_node = unpack_sensor_data(c, &q))){
                printf("failure in unpack_sensor_data\n");
                return 1;
            }
        } else if (node == -1) {
            //we generated an injector sensor packet. So test that
            if(!(other_node = unpack_sensor_data(c, &q))){
                printf("failure in unpack_sensor_data\n");
                return 1;
            }
        } else {
            //this should never happen
            printf("wtf pack_sensor data returned an invalid value\n");
            return 1;
        }
        if(node != other_node){
            printf("failure in determining sensor data source\n");
            printf("generated data was from %s\n", (node == 1) ? "VENT" : "INJ");
            printf("recovered data was from %s\n", (other_node == 1)? "VENT" : "INJ");
            printf("data string was: ");
            for(int i = 0; i < SENSOR_DATA_LENGTH; i++)
                printf("%c", c[i]);
            printf("\n");
            return 1;
        }
        if(q.pressure != s.pressure){
            printf("q.pressure: %u, s.pressure: %u\n", q.pressure, s.pressure);
            return 1;
        } else if(q.valve_limitswitch_open != s.valve_limitswitch_open) {
            printf("q.valve_limitswitch_open: %u, s.valve_limitswitch_open: %u\n", q.valve_limitswitch_open, s.valve_limitswitch_open);
            return 1;
        }else if(q.valve_limitswitch_closed!=s.valve_limitswitch_closed){
            printf("q.valve_limitswitch_closed: %u, s.valve_limitswitch_closed: %u\n", q.valve_limitswitch_closed, s.valve_limitswitch_closed);
            return 1;
        }
        for(int i = 0; i < NUM_THERMISTORS; i++){
            if(q.thermistor_data[i] != s.thermistor_data[i]){
                printf("q.thermistor_data[%i]: %u, s.thermistor_data[%i]: %u\n", i, q.thermistor_data[i], i, s.thermistor_data[i]);
                return 1;
            }
        }
    }
    return 0;
}
