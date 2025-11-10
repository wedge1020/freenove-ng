LIBS = -lwiringPi
CXXLIBS = $(LIBS) -lLED
CXXFLAGS = -Wall -fPIC
INC = 
CXX = g++
PROJ = LED
all: $(PROJ)

debug: CFLAGS += -DDEBUG -g
debug: DEBUG = debug
debug: $(PROJ)

$(PROJ):
	$(CXX) $(CXXFLAGS) -c $(PROJ).cc -o $(PROJ).o $(LIBS)
	$(CXX) -shared $(CXXFLAGS) -o lib$(PROJ).so $(PROJ).o $(LIBS)

install:
	@echo -n "Initializing installation directories ... "
	@/bin/mkdir -p   /usr/include        /usr/lib && echo -n ".."  || exit
	@/bin/chmod 0755 /usr/include        /usr/lib && echo -n ".. " || exit
	@echo "done"
	@/bin/cp    -v   $(PROJ).h           /usr/include/
	@/bin/cp    -v   lib$(PROJ).so       /usr/lib/
	@/usr/sbin/ldconfig
	@/bin/chmod 0644 /usr/include/$(PROJ).h
	@/bin/chmod 0644 /usr/lib/lib$(PROJ).so
	@echo "INSTALLATION COMPLETE"

clean:
	@rm -vrf .*.sw[op] *.o lib$(PROJ).so *.save* *~ core
