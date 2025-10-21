LIBS = -lm -lwiringPi -lADCDevice
CFLAGS = -Wall --std=gnu18
INC = 
CC = gcc
PROJ = joystick
all: $(PROJ)

debug: CFLAGS += -DDEBUG -g
debug: DEBUG = debug
debug: $(PROJ)

$(PROJ):
	$(CC) $(CFLAGS) $(PROJ).c -o $(PROJ) $(LIBS)

clean:
	@rm -vrf .*.sw[op] *.o $(PROJ) *.save* *~ core
