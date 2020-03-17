COMPILE       = $(CXX) $(CFLAGS) $(CPPFLAGS) $(INCLUDES) $(MACRO) $(OPTIONS)
CXX           = /usr/local/bin/g++-8
CPPFLAGS     += -std=c++11
INCLUDES      = -I../include
MACRO         = -DSIMULATOR
OUTPUT_OPTION = -o $@

TESTLINK = -pthread -lgtest_main -lgtest
VPATH    = ../src

TARGETS = MatrixBuffer String5x7Buffer String5x7Buffer
OBJECTS = LEDMatrix MatrixBuffer String5x7Buffer MatrixUtils

testTARGETS     = $(addprefix test, $(TARGETS))
testTARGETS.out = $(addsuffix .out, $(testTARGETS))
OBJECTS.o       = $(addsuffix .o  , $(OBJECTS))

.PHONY:	test builds clean
test:	builds clean;
builds:	$(testTARGETS.out);

%.out:	%.o $(OBJECTS.o)
	$(COMPILE) $(OUTPUT_OPTION) $(TESTLINK) $^
	./$@

%.o:	%.cpp
	$(COMPILE) $(OUTPUT_OPTION) $< -c

clean:
	rm *.out
