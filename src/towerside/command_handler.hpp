#ifndef COMMAND_HANDLER_H
#define COMMAND_HANDLER_H

#include "common/mock_arduino.hpp"
#include "common/communication/receiver.hpp"
#include "common/shared_types.hpp"
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

class Actuators: public DoubleCommandHandler {
  public:
    Actuators(const ActuatorCommand &initial_states): DoubleCommandHandler{initial_states} {
      apply(initial_states);
    }
    void apply(const ActuatorCommand &cmd) override {
      for (uint8_t i = 0; i < NUM_ACTUATORS; i++) {
        ActuatorID::ActuatorID id = static_cast<ActuatorID::ActuatorID>(i);
        Config::get_actuator(id)->set(cmd.get_actuator(id));
      }
    }
};

class SevenSeg: public DoubleCommandHandler, public Tickable {
  //array of segements that must be displayed to display the correct number
  constexpr static uint8_t digitMap[] = {
    // GFEDCBA            7-segment map:
    0b00111111, // "0"          AAA
    0b00000110, // "1"         F   B
    0b01011011, // "2"         F   B
    0b01001111, // "3"          GGG
    0b01100110, // "4"         E   C
    0b01101101, // "5"         E   C
    0b01111101, // "6"          DDD  DP
    0b00000111, // "7"
    0b01111111, // "8"
    0b01101111, // "9"
    0b01110111, // "A"
    0b01111100, // "b"
    0b00111001, // "C"
    0b01011110, // "d"
    0b01111001, // "E"
    0b01110001  // "F"
  };
  constexpr static uint8_t pinoutMap[] = {
    Pinout::SEVENSEG_A,
    Pinout::SEVENSEG_B,
    Pinout::SEVENSEG_C,
    Pinout::SEVENSEG_D,
    Pinout::SEVENSEG_E,
    Pinout::SEVENSEG_F,
    Pinout::SEVENSEG_G
  };
  void set_digit(uint8_t digit, uint8_t value) {
    digitalWrite(Pinout::SEVENSEG_D1, digit == 0);
    digitalWrite(Pinout::SEVENSEG_D2, digit == 1);
    for (uint8_t i = 0; i < 7; i++) {
      digitalWrite(pinoutMap[i], digitMap[value] & (1 << i));
    }
    digitalWrite(Pinout::SEVENSEG_DP, !has_contact);
  }
  bool has_contact = true;
  uint8_t current_digit = 0;
  uint8_t digit_values[2] = {0, 0};
  public:
    SevenSeg(const ActuatorCommand &initial_states): DoubleCommandHandler{initial_states} {
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
