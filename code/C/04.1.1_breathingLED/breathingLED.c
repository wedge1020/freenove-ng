//
// Filename:    breathingLED.c
// Description: simulate a "breathing" LED with software PWM
// Components:  LED
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
#include <softPwm.h>

#define  LEDpin    1  // wiringPi GPIO pin

int32_t  main (void)
{
    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Declare and initialize variables
    //
    int32_t  level        = 0;

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
    // Initialize LEDpin for software PWM operation, with a range from 0 to 100
    //
    softPwmCreate (LEDpin, 0, 100);

    fprintf (stdout, "Program is starting (CTRL-c to interrupt) ...\n");

    while (1)
    {
        ////////////////////////////////////////////////////////////////////////////////
        //
        // adjust the LED gradually from fully OFF (0) to fully ON (100), one step at
        // a time
        //
        for (level = 0; level < 100; level++)
        {
            softPwmWrite (LEDpin, level);
            delay (20);
        }

        ////////////////////////////////////////////////////////////////////////////////
        //
        // strategic delay for better user perception
        //
        delay (300);

        ////////////////////////////////////////////////////////////////////////////////
        //
        // adjust the LED gradually from fully ON (100) to fully OFF (0), one step at
        // a time
        //
        for (level = 100; level >= 0; level--)
        {
            softPwmWrite (LEDpin, level);
            delay (20);
        }

        ////////////////////////////////////////////////////////////////////////////////
        //
        // strategic delay for better user perception
        //
        delay (300);
    }

    return (0);
}

