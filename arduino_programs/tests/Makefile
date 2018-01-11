CC = gcc
CXX = g++

VPATH += ..

INCLUDES = -I..

TESTS = shared_type_tests

OBJS  = shared_type_tests.o
OBJS += shared_types.o

.PHONY: all
all: $(TESTS)
	@for i in $(TESTS); \
	  do ./$$i; \
	done

shared_type_tests: $(OBJS)
	@$(CC) -o $@ $(OBJS)

%.o: %.c
	@$(CC) $(INCLUDES) $(CFLAGS) -c $< -o $@

%.o: %.cpp
	@$(CXX) $(INCLUDES) $(CXXFLAGS) -c $< -o $@

.PHONY: clean
clean:
	-@rm $(TESTS) $(OBJS)
