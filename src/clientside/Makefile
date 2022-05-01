CXX = g++
CXXFLAGS = -Wall -MMD -g
EXEC = clientside
SOURCES = $(wildcard ./*.cpp ./*.ino)
ALLCPP = ${SOURCES:.ino=.cpp}
OBJECTS = ${ALLCPP:.cpp=.o}
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

%.o: %.ino
	${CXX} ${CXXFLAGS} -c -x c++ $<

.PHONY: run grind clean

run: ${EXEC}
	./${EXEC}

grind: ${EXEC}
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -s ./${EXEC}

clean:
	rm ${OBJECTS} ${DEPENDS} ${EXEC}
