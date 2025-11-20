LIBS = -lwiringPi
CLIBS = $(LIBS) -lDHT
CFLAGS = -Wall -fPIC --std=gnu18
INC = 
CC = gcc
PROJ = DHT
all: $(PROJ)

debug: CFLAGS += -DDEBUG -g
debug: DEBUG = debug
debug: $(PROJ)

$(PROJ):
	$(CC) $(CFLAGS) -c $(PROJ).c -o $(PROJ).o $(LIBS)
	$(CC) -shared $(CFLAGS) -o lib$(PROJ).so $(PROJ).o $(LIBS)

install:
	@echo -n "Initializing installation directories ... "
	@/bin/mkdir -p   /usr/include        /usr/lib && echo -n ".."  || exit
	@/bin/chmod 0755 /usr/include        /usr/lib && echo -n ".. " || exit
	@echo "done"
	@/bin/cp    -v   $(PROJ).h     /usr/include/
	@/bin/cp    -v   lib$(PROJ).so /usr/lib/
	@/usr/sbin/ldconfig
	@/bin/chmod 0644 /usr/include/$(PROJ).h
	@/bin/chmod 0644 /usr/lib/lib$(PROJ).so
	@echo "INSTALLATION COMPLETE"

clean:
	@rm -vrf .*.sw[op] *.o lib$(PROJ).so *.save* *~ core
