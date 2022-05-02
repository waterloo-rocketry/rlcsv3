CXX = g++
CXXFLAGS = -Wall -MMD -g
EXEC = towerside
SOURCES = $(wildcard ./*.cpp ./*.ino ./common/mock_arduino.cpp)
ALLCPP = ${SOURCES:.ino=.cpp}
OBJECTS = ${ALLCPP:.cpp=.o}
DEPENDS = ${OBJECTS:.o=.d}

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
	arduino-cli compile --fqbn arduino:avr:mega:cpu=atmega2560

flash: build
	arduino-cli upload -p /dev/ttyUSB* --fqbn arduino:avr:mega:cpu=atmega2560

monitor:
	arduino-cli monitor -p /dev/ttyUSB* -c baudrate=115200
