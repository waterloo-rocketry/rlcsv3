CC = gcc
CXX = g++

CFLAGS = -DNODE_TEST
CXXFLAGS = -DNODE_TEST
VPATH += ..

INCLUDES = -I..
INCLUDES+= -I.

TESTS = shared_type_tests
TESTS+= nodeio_ioio_tests

OBJS  = shared_type_tests.o
OBJS += shared_types.o
OBJS += nodeio_ioio_tests.o
OBJS += nodeio.ioio.o

.PHONY: all
all: $(TESTS)
	@for i in $(TESTS); \
	  do ./$$i; \
	done

shared_type_tests: shared_type_tests.o shared_types.o
	@$(CC) -o $@ $^

nodeio_ioio_tests: nodeio_ioio_tests.o nodeio.ioio.o
	@$(CC) -o $@ $^

%.o: %.c
	@$(CC) $(INCLUDES) $(CFLAGS) -c $< -o $@

%.o: %.cpp
	@$(CXX) $(INCLUDES) $(CXXFLAGS) -c $< -o $@

.PHONY: clean
clean:
	-@rm $(TESTS) $(OBJS)
