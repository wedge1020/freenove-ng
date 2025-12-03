LIBS = -lm -lwiringPi -lADCDevice
CXXLIBS = $(LIBS)
CXXFLAGS = -Wall
INC = 
CC = gcc
PROJ = nightlamp
all: $(PROJ)

debug: CFLAGS += -DDEBUG -g
debug: DEBUG = debug
debug: $(PROJ)

$(PROJ):
	$(CXX) $(CXXFLAGS) $(PROJ).cc -o $(PROJ) $(CXXLIBS)

clean:
	@rm -vrf .*.sw[op] *.o $(PROJ) *.save* *~ core
