COMPILE       = $(CXX) $(CFLAGS) $(CPPFLAGS) $(INCLUDES) $(MACRO) $(OPTIONS)
CXX           = g++-8
CPPFLAGS     += -std=c++14
INCLUDES      = -I../include
MACRO         = -DSIMULATOR
OUTPUT_OPTION = -o $@

TESTLINK = -pthread -lgtest_main -lgtest
VPATH    = ../src

TARGETS = MatrixBuffer String5x7Buffer LEDMatrix
OBJECTS = LEDMatrix MatrixBuffer String5x7Buffer MatrixUtils

testTARGETS     = $(addprefix test, $(TARGETS))
testTARGETS.out = $(addsuffix .out, $(testTARGETS))
OBJECTS.o       = $(addsuffix .o  , $(OBJECTS))

.PHONY:	test
test:	build clean;

.PHONY:	build
build:	$(testTARGETS.out);

%.out:	%.o $(OBJECTS.o)
	$(COMPILE) $(OUTPUT_OPTION) $(TESTLINK) $^
	./$@

%.o:	%.cpp
	$(COMPILE) -c $(OUTPUT_OPTION) $<

.PHONY:	clean
clean:
	rm *.out
