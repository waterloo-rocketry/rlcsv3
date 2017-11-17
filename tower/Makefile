CC = avr-gcc
CXX = avr-g++
DEFINES = -DF_CPU=16000000L -DARDUINO=10612 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR
MICRO = -mmcu=atmega2560
CFLAGS = -std=gnu11 $(MICRO) $(DEFINES)
CXXFLAGS = -std=gnu++11 $(MICRO) $(DEFINES)
ELFFLAGS = -w -Os -flto -fuse-linker-plugin -Wl,--gc-sections,--relax -mmcu=atmega2560
INCLUDES = -I/Users/aaronmorrison/Arduino.app/Contents/Java/hardware/arduino/avr/cores/arduino -I/Users/aaronmorrison/Arduino.app/Contents/Java/hardware/arduino/avr/variants/mega

VPATH += ..
VPATH += /Users/aaronmorrison/Arduino.app/Contents/Java/hardware/arduino/avr/cores/arduino/

objects  =tower_globals.o
objects +=tower_main.o
objects +=radio_comms.o
objects +=shared_types.o
objects +=tower_fsm.o

lib_objects  = wiring_pulse.o
lib_objects += WInterrupts.o
lib_objects += hooks.o
lib_objects += wiring.o
lib_objects += wiring_analog.o
lib_objects += wiring_digital.o
lib_objects += wiring_shift.o
lib_objects += CDC.o
lib_objects += HardwareSerial.o
lib_objects += HardwareSerial0.o
lib_objects += HardwareSerial1.o
lib_objects += HardwareSerial2.o
lib_objects += HardwareSerial3.o
lib_objects += IPAddress.o
lib_objects += PluggableUSB.o
lib_objects += Print.o
lib_objects += Stream.o
lib_objects += Tone.o
lib_objects += USBCore.o
lib_objects += WMath.o
lib_objects += WString.o
lib_objects += abi.o
lib_objects += main.o
lib_objects += new.o
lib_objects += abi.o

all:  tower.hex

tower.hex: tower.elf
	avr-objcopy -O ihex -R .eeprom tower.elf tower.hex

tower.elf: $(objects) core.a 
	$(CC) $(ELFFLAGS) -o $@ $(objects) core.a -lm

core.a: $(lib_objects)
	-rm core.a
	avr-ar rcs core.a $^

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

.PHONY: clean
clean:
	-rm *.o
	-rm core.a
	-rm tower.elf
	-rm tower.eep
	-rm tower.hex

