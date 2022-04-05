CXX = g++
CXXFLAGS = -Wall -MMD -g
EXEC = towerside
SUITE = suite.txt
SOURCES = $(wildcard ./*.cpp ./*.ino common/*.cpp)
$(info $(SOURCES))
ALLCPP = ${SOURCES:.ino=.cpp}
OBJECTS = ${ALLCPP:.cpp=.o}
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

%.o: %.ino
	${CXX} ${CXXFLAGS} -c -x c++ $<

.PHONY: run grind test clean

run: ${EXEC}
	./${EXEC}

grind: ${EXEC}
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -s ./${EXEC}

test: ${EXEC}
	cd tests; ../../../runSuite ${SUITE} ../${EXEC}

clean:
	rm ${OBJECTS} ${DEPENDS} ${EXEC}
