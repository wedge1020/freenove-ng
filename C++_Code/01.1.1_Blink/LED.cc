/***
 *** Filename    : LED.cc
 *** Description : libLED C++ class library
 *** Auther      : Matthew Haas
 *** Modification: 2025/10/04
 ***
 **************************************************************************************/

#include <wiringPi.h>
#include <stdio.h>
#include <string.h>
#include "LED.h"

LED :: LED (int pin) {
    this -> pin           = pin;
    this -> state         = LOW;    
    pinMode (pin, OUTPUT);
}

LED :: LED (int pin, int state) {
    this -> pin           = pin;
    this -> state         = state;    
    pinMode (pin, OUTPUT);
}

int  LED :: getPin (void) {
    return (this -> pin);
}

char * LED :: getState (void) {
    char result[6];

    if (this -> state    == HIGH) {
        strncpy (result, "HIGH", 5);
    }
    else {
        strncpy (result, "LOW",  5);
    }

    return (result);
}

void LED :: toggle (void) {
    if (this -> state    == LOW) {
        this -> state     = HIGH;
    }
    else {
        this -> state     = LOW;
    }
    digitalWrite (this -> pin, this -> state);
}

void LED :: write (int state) {
    this -> state         = state;
    digitalWrite (this -> pin, this -> state);
}
