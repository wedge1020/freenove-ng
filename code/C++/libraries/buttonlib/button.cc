//
// Filename:    button.cc
// Description: buttonlib C++ class library for use with freenove-ng tutorial code
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
#include "button.h"

////////////////////////////////////////////////////////////////////////////////////////
//
// Single-Parametered constructor: initialize specified wiringPi pin for standard
// button use
//
button :: button (int pin) {
    this -> pin           = pin;
    this -> state         = PUD_UP;    
    pinMode (this -> pin, INPUT);
    pullUpDnControl (this -> pin, this -> state);
}

////////////////////////////////////////////////////////////////////////////////////////
//
// Double-Parametered constructor: initialize specified wiringPi pin for standard
// button use at specified initial state (HIGH, LOW)
//
button :: button (int pin, int updnstate) {
    this -> pin           = pin;
    this -> state         = updnstate;    
    pinMode (this -> pin, INPUT);
    pullUpDnControl (this -> pin, this -> state);
}

////////////////////////////////////////////////////////////////////////////////////////
//
// getPin(): return the wiringPi pin configured for this button instance
//
int  button :: getPin (void) {
    return (this -> pin);
}

////////////////////////////////////////////////////////////////////////////////////////
//
// getState(): return a string of "HIGH" or "LOW" reflecting the current state
//             of this button instance
//
char * button :: getStateName (void) {
    char *result                   = NULL;

    result                         = (char *) malloc (sizeof (char) * 6);
    if (result                    == NULL)
    {
        fprintf (stderr, "[button] ERROR allocating memory for getState() result");
        exit (1);
    }

    if (digitalRead (this -> pin) == HIGH) {
        strncpy (result, "HIGH", 5);
    }
    else {
        strncpy (result, "LOW",  4);
    }

    return (result);
}

////////////////////////////////////////////////////////////////////////////////////////
//
// getState(): return the current state of this button instance
//
int  button :: getState (void) {
    return (digitalRead (this -> pin));
}

////////////////////////////////////////////////////////////////////////////////////////
//
// read(): set the button to the indicated `state`
//
int  button :: read (void) {
    return (digitalRead (this -> pin));
}
