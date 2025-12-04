//
// Filename:    buttonLED.cc
// Description: control LED state with BUTTON
// Components:  LED, BUTTON
//
////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////
//
// Pre-processor directives
//
#include <cstdio>
#include <cstdint>
#include <cstdlib>
#include <wiringPi.h>

#define  LEDpin     0    // GPIO wiringPi pin for LED component
#define  BUTTONpin  1    // GPIO wiringPi pin for BUTTON component

int32_t  main (void)
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
    pinMode (LEDpin,    OUTPUT);          // LED is an output component (we write it)
    pinMode (BUTTONpin, INPUT);           // BUTTON is an input component (we read it)
    pullUpDnControl (BUTTONpin, PUD_UP);  // pull up to HIGH level

    fprintf (stdout, "Program is starting (CTRL-c to interupt) ... \n");

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Display the default status (note the lack of newline at the end, so that with
    // the strategic use of backspaces, we can update this line in place)
    //
    fprintf (stdout, "BUTTON: released, LED: OFF");

    while (1)
    {
        ////////////////////////////////////////////////////////////////////////////////
        //
        // on LOW signal read, BUTTON is pressed
        //
        if (digitalRead (BUTTONpin) == LOW)
        {
            fprintf (stdout, "\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\bpressed,  LED: ON ");
            digitalWrite (LEDpin, HIGH);  // turn the LED on
        }

        ////////////////////////////////////////////////////////////////////////////////
        //
        // on HIGH signal read, BUTTON is released
        //
        else
        {
            fprintf (stdout, "\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\breleased, LED: OFF");
            digitalWrite (LEDpin, LOW);   // turn the LED off
        }
    }

    return (0);
}
