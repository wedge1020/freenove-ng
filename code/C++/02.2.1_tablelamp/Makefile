LIBS = -lm -lwiringPi
CXXLIBS = $(LIBS)
CXXFLAGS = -Wall
INC = 
CXX = gcc
PROJ = tablelamp
all: $(PROJ)

debug: CFLAGS += -DDEBUG -g
debug: DEBUG = debug
debug: $(PROJ)

$(PROJ):
	$(CXX) $(CXXFLAGS) $(PROJ).cc -o $(PROJ) $(CXXLIBS)

clean:
	@rm -vrf .*.sw[op] *.o $(PROJ) *.save* *~ core
