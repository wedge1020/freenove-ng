//
// Filename:    LED.cc
// Description: libLED C++ class library for use with freenove-ng tutorial code
// Author:      Matthew Haas
//
////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////
//
// Pre-processor directives
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wiringPi.h>
#include "LED.h"

////////////////////////////////////////////////////////////////////////////////////////
//
// Single-Parametered constructor: initialize specified wiringPi pin for standard
// LED use
//
LED :: LED (int pin) {
    this -> pin           = pin;
    this -> state         = LOW;    
    pinMode (pin, OUTPUT);
}

////////////////////////////////////////////////////////////////////////////////////////
//
// Double-Parametered constructor: initialize specified wiringPi pin for standard
// LED use at specified initial state (HIGH, LOW)
//
LED :: LED (int pin, int state) {
    this -> pin           = pin;
    this -> state         = state;    
    pinMode (pin, OUTPUT);
}

////////////////////////////////////////////////////////////////////////////////////////
//
// getPin(): return the wiringPi pin configured for this LED instance
//
int  LED :: getPin (void) {
    return (this -> pin);
}

////////////////////////////////////////////////////////////////////////////////////////
//
// getState(): return a string of "HIGH" or "LOW" reflecting the current state
//             of this LED instance
//
char * LED :: getState (void) {
    char *result          = NULL;

    result                = (char *) malloc (sizeof (char) * 6);
    if (result           == NULL)
    {
        fprintf (stderr, "[LED] ERROR allocating memory for getState() result");
        exit (1);
    }

    if (this -> state    == HIGH) {
        strncpy (result, "HIGH", 5);
    }
    else {
        strncpy (result, "LOW",  4);
    }

    return (result);
}

////////////////////////////////////////////////////////////////////////////////////////
//
// getState(): return the current state of this LED instance
//
int  LED :: getState (void) {
    return (this -> state);
}

////////////////////////////////////////////////////////////////////////////////////////
//
// toggle(): toggle the current LED state
//
void LED :: toggle (void) {
    if (this -> state    == LOW) {
        this -> state     = HIGH;
    }
    else {
        this -> state     = LOW;
    }
    digitalWrite (this -> pin, this -> state);
}

////////////////////////////////////////////////////////////////////////////////////////
//
// write(): set the LED to the indicated `state`
//
void LED :: write (int state) {
    this -> state         = state;
    digitalWrite (this -> pin, this -> state);
}
