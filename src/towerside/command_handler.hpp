#ifndef COMMAND_HANDLER_H
#define COMMAND_HANDLER_H

#include "common/mock_arduino.hpp"
#include "common/communication/receiver.hpp"
#include "common/shared_types.hpp"
#include "common/tickable.hpp"
#include "config.hpp"
#include "pinout.hpp"

namespace CommandHandler {

class DoubleCommandHandler: public Communication::MessageHandler<ActuatorCommand> {
  ActuatorCommand last_command;
  public:
    DoubleCommandHandler(const ActuatorCommand &initial_states): last_command{initial_states} {}
    void handle(const ActuatorCommand &cmd) override {
      if (cmd == last_command) {
        apply(cmd);
      }
      last_command = cmd;
    }
    virtual void apply(const ActuatorCommand &cmd) = 0;
};

class Actuators: public DoubleCommandHandler, public Tickable {
  uint8_t disarm_pin;
  ActuatorCommand last_command;
  unsigned long last_command_dispatch_timestamp = 0;
  public:
    Actuators(const ActuatorCommand &initial_states, uint8_t disarm_pin, uint8_t gnd_pin):
        DoubleCommandHandler{initial_states}, disarm_pin{disarm_pin} {
      pinMode(disarm_pin, INPUT_PULLUP);
      pinMode(gnd_pin, OUTPUT);
      digitalWrite(gnd_pin, false);
      apply(initial_states);
    }
    void apply(const ActuatorCommand &cmd) override {
      last_command = cmd;
    }
    void dispatch() {
      if (digitalRead(disarm_pin)) {
        return; // we are disarmed (pin is not pulled low), don't do anything
      }
      if (millis() - last_command_dispatch_timestamp < Config::ACTUATOR_DISPATCH_INTERVAL_MS) {
        return;
      }
      last_command_dispatch_timestamp = millis();
      for (uint8_t i = 0; i < NUM_ACTUATORS; i++) {
        ActuatorID::ActuatorID id = static_cast<ActuatorID::ActuatorID>(i);
        Config::get_actuator(id)->set(last_command.get_actuator(id));
      }
    }
    void tick() override {
      dispatch();
    }
};

class SevenSeg: public DoubleCommandHandler, public Tickable {
  //array of segements that must be displayed to display the correct number
  const static uint8_t digitMap[];
  const static uint8_t pinoutMap[];
  void set_digit(uint8_t digit, uint8_t value) {
    digitalWrite(Pinout::SEVENSEG_D1, false); // Turn both digits off to avoid cross-talk during the switch
    digitalWrite(Pinout::SEVENSEG_D2, false);
    for (uint8_t i = 0; i < 7; i++) {
      digitalWrite(pinoutMap[i], !(digitMap[value] & (1 << i))); // pins active low
    }
    if (digit == 0) {
      digitalWrite(Pinout::SEVENSEG_DP, has_contact); // show point if there is a connection issue, active low
    } else {
      digitalWrite(Pinout::SEVENSEG_DP, !digitalRead(disarm_pin)); // show point if disarmed, active low
    }
    digitalWrite(Pinout::SEVENSEG_D1, digit == 0);
    digitalWrite(Pinout::SEVENSEG_D2, digit == 1);
  }
  bool has_contact = true;
  uint8_t disarm_pin;
  uint8_t current_digit = 0;
  uint8_t digit_values[2] = {0, 0};
  public:
    SevenSeg(const ActuatorCommand &initial_states, uint8_t disarm_pin): DoubleCommandHandler{initial_states}, disarm_pin{disarm_pin} {
      pinMode(Pinout::SEVENSEG_D1, OUTPUT);
      pinMode(Pinout::SEVENSEG_D2, OUTPUT);
      for (uint8_t i = 0; i < 7; i++) {
        pinMode(pinoutMap[i], OUTPUT);
      }
      pinMode(Pinout::SEVENSEG_DP, OUTPUT);
      apply(initial_states);
    }
    void apply(const ActuatorCommand &cmd) override {
      uint8_t byte = cmd.get_byte();
      digit_values[0] = byte & 0xF;
      digit_values[1] = byte >> 4;
    }
    void set_contact(bool val) {
      has_contact = val;
    }
    void tick() override {
      current_digit = (current_digit + 1) % 2;
      set_digit(current_digit, digit_values[current_digit]);
    }
};

}

#endif
