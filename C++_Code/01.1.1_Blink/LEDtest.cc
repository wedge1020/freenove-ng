/***
 *** Filename    : Blink.c
 *** Description : libLED C++ test program (LED blinks every second)
 *** Author      : Matthew Haas
 *** Modification: 2025/10/06
 ***
 **************************************************************************************/

#include <wiringPi.h>
#include <stdio.h>
#include <LED.h>

#define  ledPin    0                                 // LED wiringPi pin number

int main (void) {    

    printf ("Program is starting ... \n");
    
    wiringPiSetup ();                                // Initialize wiringPi

    LED blink (ledPin, LOW);                         // New LED instance: blink
    
    printf ("Using pin: %d\n", blink.getPin ());     // Output information on terminal

    while(1) {
        blink.write (HIGH);                          // Set state, output information
        printf ("led turned on  (%s) >>>\n", blink.getState ());
        delay (1000);                                // Wait for 1 second

        blink.write (LOW);                           // Set state, output information
        printf ("led turned off (%s) <<<\n", blink.getState ());
        delay (1000);                                // Wait for 1 second
    }

    return (0);
}

