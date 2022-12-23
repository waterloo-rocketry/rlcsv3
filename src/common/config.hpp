#ifndef COMMON_CONFIG_H
#define COMMON_CONFIG_H

// These types act as generic containers for actuators and sensors respectively. This forces
// code to expicitely refer to actuators and sensor by their names rather than generic indexes,
// which then lets the compiler ensure that there are no mismatches.
//
// Note: The reason these are structs and not classes (and don't have constructors) is so we can use named struct initialization, ie:
//    ActuatorContainer<bool> command = {
//        .valve_1 = true,
//        .valve_2 = false,
//        ...etc
//    };
// When we compile with -Wextra, gcc will warn us about missing members.

template<typename T>
struct ActuatorContainer {
  T valve_1;
  T valve_2;
  T valve_3;
  T injector_valve;
  T ignition_primary;
  T ignition_secondary;
  T linear_actuator;
  T remote_arming;
  T remote_disarming;
};

template<typename T>
struct SensorContainer {
  // Battery Voltages
  T towerside_main_batt_mv;
  T towerside_actuator_batt_mv;
  // Actuator health
  T healthy_actuators_count;
  T towerside_state;
  // Ignition currents
  T ignition_primary_ma;
  T ignition_secondary_ma;
  // Actuator states
  T valve_1_state;
  T valve_2_state;
  T valve_3_state;
  T linear_actuator_state;
  T injector_valve_state;
};

#endif
