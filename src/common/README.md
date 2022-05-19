# RLCS Common Code

This is common code shared between both clientside and towerside. It defines the common set of actuators / sensors, and includes a few utilities and the `communication/` library.

`config.hpp` defines the common set of actuators and sensors.

`debug.hpp` provides the `DEBUG()` macro that just prints something over cerr (for when running locally).

`mock_arduino.cpp` provides (mostly) empty functions that replace the arduino builtins for when running locally.

`shared_types.hpp` defines the types common to clientside and towerside, ie the messages (ActuatorCommand and SensorData) they pass between eachother.

`tickable.hpp` provides the `Tickable` class which lets a single `trigger_tick()` function trigger `tick()` functions wherever classes need them.

`communication/connection.hpp` wraps a generic connection that lets characters to be sent/received.

`communication/decoder.hpp` defines decoders, which extract messages of a set length from a stream of characters, and the HexDecoder which decodes data of the form `W<hex bits>R`.

`communication/encoder.hpp` does the reverse by defining encoders which take an array of data and encode and send it over a connection, and the equivalent HexEncoder.

`communication/receiver.hpp` defines the `MessageReceiver` which handles interfacing a connection and a decoder, along with letting `MessageHandlers` get registered to receieve callbacks when messages are received.

`communication/sender.hpp` defines `MessageSender` which takes an encoder and a connection and lets messages be encoded and sent.

`communication/serializable.hpp` defines the generic interface for serializable messages, ie ones that can be passed to encoders and decoders.
