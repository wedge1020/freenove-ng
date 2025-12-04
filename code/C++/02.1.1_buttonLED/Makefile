LIBS = -lwiringPi
CXXLIBS = $(LIBS) -lLED -lbutton
CXXFLAGS = -Wall
INC = 
CXX = g++
PROJ = buttonLED
all: $(PROJ)

debug: CFLAGS += -DDEBUG -g
debug: DEBUG = debug
debug: $(PROJ)

$(PROJ):
	$(CXX) $(CXXFLAGS) $(PROJ).cc -o $(PROJ) $(CXXLIBS)

clean:
	@rm -vrf .*.sw[op] *.o $(PROJ) *.save* *~ core
