# Clientside Code

This code runs on the Clientside box. It mostly needs to read the missile switches to send `ActuatorCommand`s to towerside and recieve and display `SensorData`.

`channels.hpp` defines `Channel`s, which are responsible for formatting a specific sensor's numerical value to be displayed. It also defines the `Numeric` and `ActuatorState` channels for interpreting the sensor and a number and an index into the `ActuatorPosition` enum respectively.

`clientside.ino` contains the main sending loop and handles whether or not clientside is armed.

`config.cpp` sets up the channels and switches that correspond to specific sensors and actuators respectively.

`daq.cpp` handles actually reading the switches and building up an `ActuatorCommand`.

`data_handles.hpp` contains the LCD data handler which is responsible for drawing sensor data and the clientside battery voltage to the LCD.

`hardware.cpp` performs misc. hardware setup that doesn't really fit elsewhere (Serial, I2C, switch LEDs)

`pinout.hpp` defines the pin mapping of the Arduino.

`switches.hpp` defines a generic `Switch` class and then both `Missile` and `Ignition` switch types. `Missile` is a basic digital switch, `Ignition` requires two switches to be pressed and a third to be not pressed to trigger.
