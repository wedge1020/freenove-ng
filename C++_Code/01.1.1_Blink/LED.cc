/***
 *** Filename    : LED.cc
 *** Description : libLED C++ class library
 *** Auther      : Matthew Haas
 *** Modification: 2025/10/04
 ***
 **************************************************************************************/

#include <wiringPi.h>
#include <stdio.h>
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
    if (this -> state    == HIGH) {
        return ("HIGH");
    else {
        return ("LOW");
    }
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
