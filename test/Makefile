COMPILE       = $(CXX) $(CFLAGS) $(CPPFLAGS) $(INCLUDES) $(MACRO) $(OPTIONS)
CXX           = g++-8
CPPFLAGS     += -std=c++14
INCLUDES      = -I../src
MACRO         = -DSIMULATOR
OUTPUT_OPTION = -o $@

TESTLINK = -pthread -lgtest_main -lgtest
VPATH    = ../src

TARGETS      = MatrixBuffer String5x7Buffer Max7219
CORE_OBJECTS = Max7219 MatrixBuffer String5x7Buffer MatrixUtils

OBJECTS = $(addprefix core/, $(CORE_OBJECTS))

testTARGETS     = $(addprefix test, $(TARGETS))
testTARGETS.out = $(addsuffix .out, $(testTARGETS))
OBJECTS.o       = $(addsuffix .o  , $(OBJECTS))

.PHONY:	test
test:	prepare build clean;

.PHONY:	prepare
prepare:
	@mkdir core

.PHONY:	build
build:	$(testTARGETS.out);

%.out:	%.o $(OBJECTS.o)
	$(COMPILE) $(OUTPUT_OPTION) $(TESTLINK) $^
	./$@

%.o:	%.cpp
	$(COMPILE) -c $(OUTPUT_OPTION) $<

.PHONY:	clean
clean:
	rm -f *.o *.out
	rm -r core
