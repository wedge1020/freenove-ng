//
// Filename:    blink.c
// Description: libLED C++ test program (LED blinks every second)
// Requires:    libLED built/installed from the libraries/ directory
//
////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <wiringPi.h>
#include <LED.h>                                     // libLED-provided header

#define  LEDpin    0                                 // LED wiringPi pin number

int main (void) {

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Declare and initialize variables
    //
    LED *blink            = NULL;

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Bring wiringPi functionality online
    //
    if (wiringPiSetup () == -1)
    {
        std::cout << "[ERROR] Could not initialize wiringPi Library!" << std::endl;
        exit (1);
    }

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // create and initialize a new LED instance (called `blink`)
    //
    blink                 = new LED (LEDpin, LOW);

    fprintf (stdout, "Program is starting (CTRL-c to interrupt ...\n");
    fprintf (stdout, "[LED] configured for OUTPUT mode using pin: %d\n", blink.getPin ());

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Display the default status (note the lack of newline at the end, so that with
    // the strategic use of backspaces, we can update this line in place)
    //
    fprintf (stdout, "\nLED: OFF (%4s)", blink.getState ());

    while (1) {

        ////////////////////////////////////////////////////////////////////////////////
        //
        // Turn LED on
        //
        blink.write (HIGH);

        ////////////////////////////////////////////////////////////////////////////////
        //
        // update information display to report current LED state
        //
        fprintf (stdout, "\b\b\b\b\b\b\b\b\b\bON  (%4s)", blink.getState ());

        ////////////////////////////////////////////////////////////////////////////////
        //
        // strategic delay for user perception (1000mS == 1 second)
        //
        delay (1000);

        ////////////////////////////////////////////////////////////////////////////////
        //
        // Turn LED off
        //
        blink.write (LOW);

        ////////////////////////////////////////////////////////////////////////////////
        //
        // update information display to report current LED state
        //
        fprintf (stdout, "\b\b\b\b\b\b\b\b\b\bOFF (%4s)", blink.getState ());

        ////////////////////////////////////////////////////////////////////////////////
        //
        // strategic delay for user perception (1000mS == 1 second)
        //
        delay (1000);
    }

    return (0);
}

