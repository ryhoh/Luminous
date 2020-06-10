COMPILE       = $(CXX) $(CFLAGS) $(CPPFLAGS) $(INCLUDES) $(MACRO) $(OPTIONS)
CXX           = g++
CPPFLAGS     += -std=c++11
# INCLUDES      = -I./include
# MACRO         = -DSIMULATOR
OUTPUT_OPTION = -o $@

VPATH = ./src

OBJECTS   = Max7219 MatrixBuffer String5x7Buffer MatrixUtils
OBJECTS.o = $(addsuffix .o, $(OBJECTS))

ifeq ($(ARCH), SIM)
	MACRO = -DSIMULATOR
	DIR = ./build/sim/
	ARCH_OK = 1
else ifeq ($(ARCH), ARD)
	MACRO = -DARDUINO
endif

ifdef ARCH_OK
.PHONY:	lib detArch clean
lib: detArch libLEDMatrix.a clean;

libLEDMatrix.a:	$(OBJECTS.o)
	@mkdir -p $(DIR)
	ar r $(DIR)$@ $(OBJECTS.o)

%.o:	%.cpp
	$(COMPILE) $(OUTPUT_OPTION) $< -c

else  # ARCH_OK
.PHONY: usage clean
usage:
	@printf "\033[31m%s\033[m\n" "[usage] set ARCH=(SIM / ARD)"
	@printf "[info ] Arduino library is currently not available\n"
endif

clean:
	rm *.o
