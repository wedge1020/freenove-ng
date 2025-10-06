/***
 *** Filename    : LED.h
 *** Description : libLED C++ class library
 *** Author      : Matthew Haas
 *** Modification: 2025/10/04
 **************************************************************************************/

#ifndef _LED_H
#define _LED_H

class LED {
    public:
              LED      (int);         // wiringPi pin
              LED      (int, int);    // wiringPi pin, initial state (HIGH, LOW)
        int   getPin   (void);        // retrieves the wiringPi pin
        char *getState (void);        // returns "HIGH" or "LOW" for output
        int   toggle   (void);        // flip the current state
        int   write    (int);         // set the state of the LED

    private:
        int   pin;
        int   state;
}

#endif
