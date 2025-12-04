//
// Filename:    button.h
// Description: buttonlib C++ class library for use with freenove-ng tutorial code
// Author:      Matthew Haas
//
////////////////////////////////////////////////////////////////////////////////////////

#ifndef _BUTTON_H
#define _BUTTON_H

class button {
    public:
              button       (int);         // wiringPi pin
              button       (int, int);    // wiringPi pin, initial state (HIGH, LOW)
        int   getPin       (void);        // retrieves the wiringPi pin
        char *getStateName (void);        // returns "HIGH" or "LOW" for output
        int   getState     (void);        // returns the current state of the instance
        int   read         (void);        // set the state of the LED

    private:
        int   pin;
        int   state;
};

#endif
