//
// Filename:    lightwater.c
// Description: use ten segment LED bar component
// Components:  LED bar
//
////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////
//
// Pre-processor directives
//
#include <wiringPi.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define  NUM_LEDS  10

int32_t  main (void)
{
    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Declare and initialize variables
    //
    int32_t  position     = 0;
    int32_t  LEDbar[]     = { 0, 1, 2, 3, 4, 5, 6, 8, 9, 10 }; // wiringPi GPIO pins

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Bring wiringPi functionality online
    //
    if (wiringPiSetup () == -1)
    {
        fprintf (stderr, "[ERROR] Could not initialize wiringPi library!\n");
        exit (1);
    }

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // initialize each LEDbar wiringPi pin to OUTPUT mode
    //
    for (position = 0; position < NUM_LEDS; position++)
    {
        pinMode (LEDbar[position], OUTPUT);
    }

    fprintf (stdout, "Program is starting (CTRL-c to interrupt) ...\n");

    while (1)
    {
        ////////////////////////////////////////////////////////////////////////////////
        //
        // Perform a left to right display motion across the LEDbar (light up position
        // 0 through 9 (ten positions), one at a time
        //
        for (position = 0; position < NUM_LEDS; position++)
        {
            digitalWrite (LEDbar[position], LOW);
            delay (100);
            digitalWrite (LEDbar[position], HIGH);
        }

        ////////////////////////////////////////////////////////////////////////////////
        //
        // Perform a right to left display motion across the LEDbar (light up position
        // 0 through 9 (ten positions), one at a time
        //
        for (position = NUM_LEDS - 1; position >= 0; position--)
        {
            digitalWrite (LEDbar[position], LOW);
            delay (100);
            digitalWrite (LEDbar[position], HIGH);
        }
    }

    return (0);
}

