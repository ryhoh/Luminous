COMPILE       = $(CXX) $(CFLAGS) $(CPPFLAGS) $(INCLUDES) $(MACRO) $(OPTIONS)
CXX           = g++
CPPFLAGS     += -std=c++14
INCLUDES      = -I../include
MACRO         = -DSIMULATOR
OUTPUT_OPTION = -o $@

VPATH = ../src

CORE_OBJECTS = Max7219 MatrixBuffer String5x7Buffer MatrixUtils

OBJECTS = $(addprefix core/, $(CORE_OBJECTS))
OBJECTS.o = $(addsuffix .o, $(OBJECTS))


.PHONY:	build
build:	prepare scroll.out center.out speedtest.out

.PHONY:	prepare
prepare:
	@mkdir core

%.out:	%.cpp $(OBJECTS.o)
	$(COMPILE) $(OUTPUT_OPTION) $^

%.o:	%.cpp
	$(COMPILE) -c $(OUTPUT_OPTION) $<

.PHONY:	clean
clean:
	-rm -f *.o *.out
	-rm -r core
