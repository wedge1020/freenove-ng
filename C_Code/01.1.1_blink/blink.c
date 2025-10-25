//
// Filename   : blink.c
// Description: basic usage of GPIO. Let led blink.
// Components : LED
//
////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////
//
// Pre-processor directives
//
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <wiringPi.h>

#define  LEDpin    0  // GPIO wiringPi pin for LED component

int32_t  main(void)
{
    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Bring wiringPi functionality online
    //
    if (wiringPiSetup ()         == -1)
    {
        fprintf (stderr, "[ERROR] Could not initialize wiringPi library!\n");
        exit (1);
    }

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // configure the peripheral pins for the appropriate modes of operation
    //
    pinMode (LEDpin, OUTPUT);  // LED is an output component (we write it)

    fprintf (stdout, "Program is starting (CTRL-c to interrupt) ...\n");
    fprintf (stdout, "[LED] configured for OUTPUT mode using pin: %d\n", LEDpin);

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Display the default status (note the lack of newline at the end, so that with
    // the strategic use of backspaces, we can update this line in place)
    //
    fprintf (stdout, "\nLED: OFF");

    while (1)
    {
        ////////////////////////////////////////////////////////////////////////////////
        //
        // Turn LED on
        //
        digitalWrite (LEDpin, HIGH);

        ////////////////////////////////////////////////////////////////////////////////
        //
        // update information display to report current LED state
        //
        fprintf (stdout, "\b\b\bON ");

        ////////////////////////////////////////////////////////////////////////////////
        //
        // strategic delay for user perception (1000mS == 1 second)
        //
        delay (1000);

        ////////////////////////////////////////////////////////////////////////////////
        //
        // Turn LED off
        //
        digitalWrite (LEDpin, LOW);

        ////////////////////////////////////////////////////////////////////////////////
        //
        // update information display to report current LED state
        //
        fprintf (stdout, "\b\b\bOFF");

        ////////////////////////////////////////////////////////////////////////////////
        //
        // strategic delay for user perception (1000mS == 1 second)
        //
        delay (1000);
    }

    return (0);
}
