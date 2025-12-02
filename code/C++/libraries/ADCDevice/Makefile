LIBS = -lwiringPi
CXXLIBS = $(LIBS) -lADCDevice
CXXFLAGS = -Wall -fPIC
INC = 
CXX = g++
PROJ = ADC
all: $(PROJ)

debug: CFLAGS += -DDEBUG -g
debug: DEBUG = debug
debug: $(PROJ)

$(PROJ):
	$(CXX) $(CXXFLAGS) -c $(PROJ)Device.cc -o $(PROJ)Device.o $(LIBS)
	$(CXX) -shared $(CXXFLAGS) -o lib$(PROJ)Device.so $(PROJ)Device.o $(LIBS)

install:
	@echo -n "Initializing installation directories ... "
	@/bin/mkdir -p   /usr/include        /usr/lib && echo -n ".."  || exit
	@/bin/chmod 0755 /usr/include        /usr/lib && echo -n ".. " || exit
	@echo "done"
	@/bin/cp    -v   $(PROJ)Device.h           /usr/include/
	@/bin/cp    -v   lib$(PROJ)Device.so       /usr/lib/
	@/usr/sbin/ldconfig
	@/bin/chmod 0644 /usr/include/$(PROJ)Device.h
	@/bin/chmod 0644 /usr/lib/lib$(PROJ)Device.so
	@echo "INSTALLATION COMPLETE"

clean:
	@rm -vrf .*.sw[op] *.o lib$(PROJ)Device.so *.save* *~ core
