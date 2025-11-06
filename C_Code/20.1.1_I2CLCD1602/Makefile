LIBS = -lm -lwiringPi -lwiringPiDev
CFLAGS = -Wall --std=gnu18
INC = 
CC = gcc
PROJ = I2CLCD1602
all: $(PROJ)

debug: CFLAGS += -DDEBUG -g
debug: DEBUG = debug
debug: $(PROJ)

$(PROJ):
	$(CC) $(CFLAGS) $(PROJ).c -o $(PROJ) $(LIBS)

clean:
	@rm -vrf .*.sw[op] *.o $(PROJ) *.save* *~ core
