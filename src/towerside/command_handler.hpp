#ifndef COMMAND_HANDLER_H
#define COMMAND_HANDLER_H

#include "common/communicator.hpp"
#include "common/shared_types.hpp"

class ActuatorCommandHandler: public MessageHandler<ActuatorCommand> {
  ActuatorCommand last_command;
  public:
    ActuatorCommandHandler(ActuatorCommand initial_states): last_command{initial_states} {}
    void handle(ActuatorCommand cmd) override {
      if (cmd == last_command) {
      }
      last_command = cmd;
    }
};

#endif
