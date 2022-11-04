CXX = g++
CXXFLAGS = -Wall -MMD -g
EXEC = towerside
SOURCES = $(wildcard ./*.cpp ./*.ino ./common/mock_arduino.cpp)
ALLCPP = ${SOURCES:.ino=.cpp}
OBJECTS = ${ALLCPP:.cpp=.o}
DEPENDS = ${OBJECTS:.o=.d}
ARDUINO_FQBN = arduino:avr:mega:cpu=atmega2560
ARDUINO_PORT = /dev/ttyUSB0

${EXEC}: ${OBJECTS}
	${CXX} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

%.o: %.ino
	${CXX} ${CXXFLAGS} -c -x c++ $<

.PHONY: run grind clean build flash monitor

run: ${EXEC}
	./${EXEC}

grind: ${EXEC}
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -s ./${EXEC}

clean:
	rm ${OBJECTS} ${DEPENDS} ${EXEC}

build:
	arduino-cli compile --fqbn ${ARDUINO_FQBN}

flash: build
	arduino-cli upload -p ${ARDUINO_PORT} --fqbn ${ARDUINO_FQBN}

monitor:
	arduino-cli monitor -p ${ARDUINO_PORT} -c baudrate=115200
