#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#include "shared_types.h"

int checkBase64(void);
int checkActuatorCompare(void);
int randomActuatorCompare(void);

int main(int argc, char* argv[]){
    srand(time(NULL));   // should only be called once
    if(checkBase64()) {
        printf("Error on test checkBase64(), bailing\n");
        exit(1);
    }
    if(randomActuatorCompare()){
        printf("Error on test randomActuatorCompare(), bailing\n");
        exit(1);
    }
    if(checkActuatorCompare()) {
        printf("Error on test checkActuatorCompare(), bailing\n");
        exit(1);
    }
    printf("test %s passed successfully\n", argv[0]);
    exit(0);
}

int checkBase64(){
    //check that converting a char to base64 and back is the same
    //elements of this arry in [0,63]
    char to64Test[] = {0,12,16,24,63};
    for(int i = 0; i < sizeof(to64Test); i++)
       if(fromBase64(toBase64(to64Test[i])) != to64Test[i]) {
           //error. Print problem and return zero
           printf("Error converting to base 64 and back"
                   " Number failed on was %i\n", to64Test[i]);
           return 1;
       }
    
    //chack that converting a char in [a-zA-Z0-9+/] from base64 and back works
    char from64Test[] = {'a', 'q', 'B', '7', '+'};
    for(int i = 0; i < sizeof(from64Test); i++)
       if(toBase64(fromBase64(from64Test[i])) != from64Test[i]) {
           //error. Print problem and return zero
           printf("Error converting from base 64 and back"
                   " character failed on was %c\n", from64Test[i]);
           return 1;
       }
    //test passed, return 0
    return 0;
}

void generateRandomActuatorState(actuator_state_t *s){
    int r = rand();
    s->remote_fill_valve = r & 1;
    s->remote_vent_valve = (r & 2) >> 1;
    s->run_tank_valve    = (r & 4) >> 2;  
    s->injector_valve    = (r & 8) >> 3;
    s->linear_actuator   = (r & 16) >> 4;
    s->ignition_power    = (r & 32) >> 5;
    s->ignition_select   = (r & 64) >> 6;
    if(s->ignition_power)
        s->remote_fill_valve = 0;
    else
        s->ignition_select = 0;
}

int randomActuatorCompare(){
    actuator_state_t s,q;
    char binary;
    for(int i = 0; i < 100000; i++){
        generateRandomActuatorState(&s);
        convert_state_to_radio(&s, &binary);
        convert_radio_to_state(&q, binary);
        if(!actuator_compare(&s, &q))
        {
            printf("s.remote_fill_valve: %i\n",s.remote_fill_valve);
            printf("s.remote_vent_valve: %i\n",s.remote_vent_valve);
            printf("s.run_tank_valve: %i\n",s.run_tank_valve);
            printf("s.injector_valve: %i\n",s.injector_valve);
            printf("s.linear_actuator: %i\n",s.linear_actuator);
            printf("s.ignition_power: %i\n",s.ignition_power);
            printf("s.ignition_select: %i\n",s.ignition_select);
            printf("failure random actuator compare\n");
            printf("q.remote_fill_valve: %i\n",q.remote_fill_valve);
            printf("q.remote_vent_valve: %i\n",q.remote_vent_valve);
            printf("q.run_tank_valve: %i\n",q.run_tank_valve);
            printf("q.injector_valve: %i\n",q.injector_valve);
            printf("q.linear_actuator: %i\n",q.linear_actuator);
            printf("q.ignition_power: %i\n",q.ignition_power);
            printf("q.ignition_select: %i\n",q.ignition_select);
            printf("failure random actuator compare\n");
            return 1;
        }
    }
    return 0;
}

int checkActuatorCompare(){
    actuator_state_t s, q;

    s.remote_fill_valve = 1;
    s.remote_vent_valve = 1;
    s.run_tank_valve = 1;   
    s.injector_valve = 1;   
    s.linear_actuator = 1;  
    s.ignition_power = 1;   
    s.ignition_select = 1;  

    q.remote_fill_valve = 1;
    q.remote_vent_valve = 1;
    q.run_tank_valve = 1;   
    q.injector_valve = 1;   
    q.linear_actuator = 1;  
    q.ignition_power = 1;   
    q.ignition_select = 1;  

    if(!actuator_compare(&s, &q))
    {
        printf("failure in actuator compare: all 1's \n");
        return 1;
    }

    q.remote_fill_valve = 0;
    if(actuator_compare(&s, &q))
    {
        printf("failure in actuator compare: change remote_fil_valve\n");
        return 1;
    }

    q.remote_fill_valve = 1;
    q.remote_vent_valve = 0;
    if(actuator_compare(&s, &q))
    {
        printf("failure in actuator compare: change remote_vent_valve\n");
        return 1;
    }

    q.remote_vent_valve = 1;
    q.run_tank_valve = 0;
    if(actuator_compare(&s, &q))
    {
        printf("failure in actuator compare: change run_tank_valve\n");
        return 1;
    }

    q.run_tank_valve = 1;
    q.injector_valve = 0;
    if(actuator_compare(&s, &q))
    {
        printf("failure in actuator compare: change injector_valve\n");
        return 1;
    }

    q.injector_valve = 1;
    q.linear_actuator = 0;
    if(actuator_compare(&s, &q))
    {
        printf("failure in actuator compare: change linear_actuator\n");
        return 1;
    }

    q.linear_actuator = 1;
    q.ignition_power = 0;
    if(actuator_compare(&s, &q))
    {
        printf("failure in actuator compare: change ignition power\n");
        return 1;
    }

    return 0;
}
