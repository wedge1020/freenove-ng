/***
 *** Filename    : Blink.c
 *** Description : libLED C++ test program (LED blinks every second)
 *** Author      : Matthew Haas
 *** Modification: 2025/10/04
 ***
 **********************************************************************/
#include <wiringPi.h>
#include <stdio.h>
#include <LED.h>

#define  ledPin    0    // define the led pin number

int main (void) {    
    printf ("Program is starting ... \n");
    
    wiringPiSetup();    //Initialize wiringPi.

    LED blink  = new LED (ledPin, LOW);
    
    printf ("Using pin: %d\n", blink.getPin());    //Output information on terminal

    while(1) {
        blink.write (HIGH);
        printf ("led turned on (%s) >>>\n", blink.getState()); //Output information on terminal
        delay (1000);                        //Wait for 1 second
        blink.write (LOW);
        printf ("led turned off (%s) <<<\n", blink.getState());        //Output information on terminal
        delay (1000);                        //Wait for 1 second
    }

    return (0);
}

