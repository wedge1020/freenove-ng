//
// Filename:    LED.h
// Description: libLED C++ class library for use with freenove-ng tutorial code
// Author:      Matthew Haas
//
////////////////////////////////////////////////////////////////////////////////////////

#ifndef _LED_H
#define _LED_H

class LED {
    public:
              LED          (int);         // wiringPi pin
              LED          (int, int);    // wiringPi pin, initial state (HIGH, LOW)
        int   getPin       (void);        // retrieves the wiringPi pin
        char *getStateName (void);        // returns "HIGH" or "LOW" for output
        int   getState     (void);        // returns the current state of the instance
        void  toggle       (void);        // flip the current state
        void  write        (int);         // set the state of the LED

    private:
        int   pin;
        int   state;
};

#endif
