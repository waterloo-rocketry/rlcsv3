#include "shared_types.h"

//returns 1 if they're the same, else returns 0
int actuator_compare(const actuator_state_t* s, const actuator_state_t* q)
{
    return  s->remote_fill_valve == q->remote_fill_valve &&
            s->remote_vent_valve == q->remote_vent_valve &&
            s->run_tank_valve == q->run_tank_valve &&
            s->injector_valve == q->injector_valve &&
            s->linear_actuator == q->linear_actuator &&
            s->ignition_power == q->ignition_power &&
            s->ignition_select == q->ignition_select;
}
