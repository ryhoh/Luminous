COMPILE       = $(CXX) $(CFLAGS) $(CPPFLAGS) $(INCLUDES) $(MACRO) $(OPTIONS)
CXX           = g++
CPPFLAGS     += -std=c++11
MACRO         = -DSIMULATOR
OUTPUT_OPTION = -o $@

VPATH = ../src

OBJECTS   = LEDMatrix MatrixBuffer String5x7Buffer MatrixUtils
OBJECTS.o = $(addsuffix .o, $(OBJECTS))

.PHONY: clean

simulator:	simulator.cpp $(OBJECTS.o)
	$(COMPILE) $(OUTPUT_OPTION) $^
	./$@

%.o:	%.cpp
	$(COMPILE) $(OUTPUT_OPTION) $< -c

clean:
	rm *.o
