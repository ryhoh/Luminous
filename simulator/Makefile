COMPILE       = $(CXX) $(CFLAGS) $(CPPFLAGS) $(INCLUDES) $(MACRO) $(OPTIONS)
CXX           = g++
CPPFLAGS     += -std=c++14
MACRO         = -DSIMULATOR
OUTPUT_OPTION = -o $@

VPATH = ../src

OBJECTS   = Max7219 MatrixBuffer String5x7Buffer MatrixUtils
OBJECTS.o = $(addsuffix .o, $(OBJECTS))

.PHONY: run
run:	simulator clean
	./simulator

.PHONY:	build
build:	simulator;

simulator:	simulator.cpp $(OBJECTS.o)
	$(COMPILE) $(OUTPUT_OPTION) $^

%.o:	%.cpp
	$(COMPILE) -c $(OUTPUT_OPTION) $<

.PHONY:	clean
clean:
	rm *.o
