COMPILE       = $(CXX) $(CFLAGS) $(CPPFLAGS) $(INCLUDES) $(MACRO) $(OPTIONS)
CXX           = g++
CPPFLAGS     += -std=c++14
INCLUDES      = -I../src
MACRO         = -DSIMULATOR
OUTPUT_OPTION = -o $@

VPATH = ../src

CORE_OBJECTS = Max7219 MatrixBuffer String5x7Buffer MatrixUtils

OBJECTS = $(addprefix core/, $(CORE_OBJECTS))
OBJECTS.o = $(addsuffix .o, $(OBJECTS))

.PHONY: run
run:	build clean
	./simulator

.PHONY:	build
build:	prepare simulator;

.PHONY:	prepare
prepare:
	@mkdir core

simulator:	simulator.cpp $(OBJECTS.o)
	$(COMPILE) $(OUTPUT_OPTION) $^

%.o:	%.cpp
	$(COMPILE) -c $(OUTPUT_OPTION) $<

.PHONY:	clean
clean:
	rm -f *.o
	rm -r core
