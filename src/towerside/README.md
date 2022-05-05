# RLCS Towerside Code

This code runs on the Arduino inside Towerside. The high-level idea is that clientside sends us its desired actuator state (in the form of an `ActuatorCommand` message) repeatedly, we need to handle those messages and a) tell the actuators what to do b) show that state on the 7-segment display. At the same time it needs to sample local sensors (ie actuator positions and current draws, analog inputs for stuff like battery voltages, DAQ data) and send that all over to clienside (in a `SensorData` message) to be displayed / passed on to a computer.

`actuators.hpp` defines the generic `Actuator` class which provides a generic interface to all actuators (setting the position, getting info such as limit switches and current, health check). It also defines the `I2C` actuator (a relay board) and the `RocketRadio` actuator (a copy of actuator board on the rocket CAN bus, talked to through live telemetry breakout).

`command_handler.cpp` initializes the static fields in the 7-segment handler, which includes the map from digits to led segments and the pin definitions.

`command_handler.hpp` defines the various handlers that act on recieved acuator commands from client side. `DoubleCommandHandler` is an abstract layer which only passes the command on to its subclass if the previous command recieved was identical. This means that for any valves to actuate client side needs to send two commands in a row, so if one command gets messed up nothing changes. `Actuators` handles applying commands to the actuators. `SevenSeg` handles updating the 7-segment display with desired state, along with showing whether there is a communiction issue and if towerside is disarmed.

`config.cpp` defines the mapping of ActuatorIDs to actuators (eg I2C vs RocketRadio actuators) and from SensorIDs to sensors (eg analog input, actuator current). It also defines the default and safe states for the actuators.

`daq.cpp` aggregates all of the sensor values into a SensorData messages.

`hardware.cpp` performs misc. hardware-specific setup (eg initializing serial, I2C).

`pinout.hpp` defines the mapping of pin functions to pins numbers.

`sensors.hpp` defines the generic `Sensor` class for data that can get sent back to client side. It then defines various sensors such as actuator position and currents, number of healthy actuators, and analog inputs.

`towerside.ino` is the main entrypoint, it has the main loop that ticks everything and sends messages to clientside.
