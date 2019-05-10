CC = gcc
CXX = g++

CFLAGS = -DNODE_TEST
CXXFLAGS = -DNODE_TEST
VPATH += ../client_arduino_ide

INCLUDES = -I../client_arduino_ide
INCLUDES+= -I.

TESTS = shared_type_tests
TESTS+= rlcslog_tests

OBJS  = shared_type_tests.o
OBJS += shared_types.o
OBJS += rlcslog_tests.o
OBJS += sd_handler.o

.PHONY: all
all: $(TESTS)
	@for i in $(TESTS); \
	  do ./$$i; \
	done

shared_type_tests: shared_type_tests.o shared_types.o
	@$(CC) -o $@ $^

rlcslog_tests: rlcslog_tests.o sd_handler.o shared_types.o
	@$(CC) -o $@ $^

sd_handler.o: sd_handler.cpp SD.h
	@$(CXX) $(INCLUDES) $(CXXFLAGS) -DCLIENT -DTOWER -c $< -o $@

%.o: %.c SD.h
	@$(CC) $(INCLUDES) $(CFLAGS) -c $< -o $@

%.o: %.cpp SD.h
	@$(CXX) $(INCLUDES) $(CXXFLAGS) -c $< -o $@

.PHONY: clean
clean:
	-@rm $(TESTS) $(OBJS)
