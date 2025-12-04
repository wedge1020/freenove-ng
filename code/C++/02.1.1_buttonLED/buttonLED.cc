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
#include <LED.h>
#include <button.h>

#define  LEDpin     0    // GPIO wiringPi pin for LED component
#define  BUTTONpin  1    // GPIO wiringPi pin for BUTTON component

int32_t  main (void)
{
    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Declare and initialize variables
    //
    LED    *light                   = NULL;
    button *lightswitch             = NULL;

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Bring wiringPi functionality online
    //
    if (wiringPiSetup ()           == -1)
    {
        fprintf (stderr, "[ERROR] Could not initialize wiringPi library!\n");
        exit (1);
    }

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // configure the peripheral pins for the appropriate modes of operation
    //
    light                           = new LED (LEDpin);
    lightswitch                     = new button (BUTTONpin);

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
        if (lightswitch -> read () == LOW)
        {
            fprintf (stdout, "\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\bpressed,  LED: ON ");
            light -> write (HIGH);  // turn the LED on
        }

        ////////////////////////////////////////////////////////////////////////////////
        //
        // on HIGH signal read, BUTTON is released
        //
        else
        {
            fprintf (stdout, "\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\breleased, LED: OFF");
            light -> write (LOW);   // turn the LED off
        }
    }

    return (0);
}
