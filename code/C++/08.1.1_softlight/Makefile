LIBS = -lm -lwiringPi -lADCDevice
CXXLIBS = $(LIBS) -lLED
CXXFLAGS = -Wall
INC = 
CC = g++
PROJ = softlight
all: $(PROJ)

debug: CFLAGS += -DDEBUG -g
debug: DEBUG = debug
debug: $(PROJ)

$(PROJ):
	$(CXX) $(CXXFLAGS) $(PROJ).cc -o $(PROJ) $(CXXLIBS)

clean:
	@rm -vrf .*.sw[op] *.o $(PROJ) *.save* *~ core
