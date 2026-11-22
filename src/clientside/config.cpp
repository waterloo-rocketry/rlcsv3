#include "config.hpp"
#include "common/mock_arduino.hpp"
#include "pinout.hpp"

namespace config {

const uint8_t AUTOSEQ_MODE_PIN = pinout::MISSILE_SWITCH_7;

enum class SeqState : uint8_t {
  IDLE,
  IGNITING,
  WAITING_FOR_VALVE,
  VALVE_ACTUATED
};

static SeqState seq_state = SeqState::IDLE;
static unsigned long fire_press_start = 0;
static unsigned long last_fire_time = 0;
static unsigned long stage_start = 0;
static unsigned long current_drop_start = 0;
static bool current_flowing = false;

void reset_autosequence() {
  seq_state = SeqState::IDLE;
  fire_press_start = 0;
  stage_start = 0;
  current_drop_start = 0;
  current_flowing = false;
}

void update_autosequence(uint16_t ignition_ma) {
  if (!digitalRead(AUTOSEQ_MODE_PIN)) {
    reset_autosequence();
    return;
  }

  unsigned long now = millis();
  bool raw_fire = digitalRead(pinout::MISSILE_SWITCH_IGNITION_PRI) &&
                  !digitalRead(pinout::MISSILE_SWITCH_IGNITION_FIRE);

  //Record the time since pressing the fire button in fire_press_start
  if (raw_fire) {
    last_fire_time = now;
    if (fire_press_start == 0) fire_press_start = now;
  } else {
    if (seq_state == SeqState::IDLE) fire_press_start = 0;
  }

  // Ensure the autosequencing aborts only if it has been false for 50 ms
  bool fire_held = raw_fire || (seq_state != SeqState::IDLE && (now - last_fire_time < 50));
  if (seq_state != SeqState::VALVE_ACTUATED) {
    if (!fire_held) {
      reset_autosequence();
      return;
    }
  }

  switch (seq_state) {
    case SeqState::IDLE:
      // Must hold for at least 50ms before starting to prevent accidental pressed starting the autosequence
      if (now - fire_press_start >= 50) {
        seq_state = SeqState::IGNITING;
        stage_start = now;
        current_flowing = false;
        current_drop_start = 0;
      }
      break;

    case SeqState::IGNITING:
      if (ignition_ma == SENSOR_ERR_VAL) {
        break;
      }
      if (!current_flowing) {
        // Confirm igniter is drawing current (>= 1.5A)
        if (ignition_ma >= 1500) {
          current_flowing = true;
          current_drop_start = 0;
        }
        break;
      } 

      // Ensure we remain in this state while current is flowing
      if (ignition_ma >= 1500) {
        current_drop_start = 0; // Current still high or bounced back up
        break;
      }
      
      // We will only make it here if ignition_ma < 1500 from the above statement
      // We then check how long the current has been below 1500 for
      if(current_drop_start == 0){
        current_drop_start = now;
      } //only start the valve_delay if the current has dropped below 1500 for over 50ms
      else if (now - current_drop_start >= 200){
        seq_state = SeqState::WAITING_FOR_VALVE;
            stage_start = now;
        }
      break;

    case SeqState::WAITING_FOR_VALVE:
      //One second delay after current drop and we have fire
      if (now - stage_start >= 1000) {
        seq_state = SeqState::VALVE_ACTUATED;
      }
      break;

    case SeqState::VALVE_ACTUATED:
      break;

  }

}
  
static bool autosequence_ignition_active() {
  return seq_state != SeqState::IDLE;
}
static bool autosequence_valve_active() {
  return seq_state == SeqState::VALVE_ACTUATED;
}

ActuatorMessage build_command_message() {

  bool autoseq_mode = digitalRead(AUTOSEQ_MODE_PIN);
  return ActuatorMessage{
      .ov101 = digitalRead(pinout::MISSILE_SWITCH_1),
      .ov102 = digitalRead(pinout::MISSILE_SWITCH_2),
      .ov103 = digitalRead(pinout::MISSILE_SWITCH_3),
      .nv201 = digitalRead(pinout::MISSILE_SWITCH_4),
      .cdv401 = digitalRead(pinout::MISSILE_SWITCH_5),
      .cdv402 = digitalRead(pinout::MISSILE_SWITCH_6),
      .qd301 =
          !autoseq_mode ? digitalRead(pinout::MISSILE_SWITCH_IGNITION_SEC)
                        : autosequence_valve_active(),
      .pyro_valve = digitalRead(pinout::MISSILE_SWITCH_INJECTOR),
      .rocket_charging = 0,
      .tank_heating_1 = digitalRead(pinout::MISSILE_SWITCH_8),
      .tank_heating_2 = digitalRead(pinout::MISSILE_SWITCH_8),
      .ignition_primary =
          !autoseq_mode ? (digitalRead(pinout::MISSILE_SWITCH_IGNITION_PRI) &&
                           !digitalRead(pinout::MISSILE_SWITCH_IGNITION_FIRE))
                        : autosequence_ignition_active(),
      .ignition_secondary = // fire secondary ignition with primary ignition switch
          !autoseq_mode ? (digitalRead(pinout::MISSILE_SWITCH_IGNITION_PRI) &&
                           !digitalRead(pinout::MISSILE_SWITCH_IGNITION_FIRE))
                        : autosequence_ignition_active(),
  };
}

} // namespace config
