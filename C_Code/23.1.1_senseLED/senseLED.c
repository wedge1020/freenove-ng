//
// Filename:    senseLED.c
// Description: Control LED with infrared Motion sensor
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

#define  LEDpin    1                   // wiringPi GPIO pin the LED is plugged into
#define  SENSORpin 0                   // wiringPi GPIO pin the SENSOR is plugged into

int32_t  main (void)
{
    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Bring wiringPi functionality online
    //
    if (wiringPiSetup ()            == -1)
    {
        fprintf (stderr, "[ERROR] Could not initialize wiringPi library!\n");
        exit (1);
    }

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Configure the LED and SENSOR as appropriate
    //
    pinMode (LEDpin,    OUTPUT);
    pinMode (SENSORpin, INPUT);

    fprintf (stdout, "Program is starting (CTRL-c to interrupt) ...\n\n");
    fprintf (stdout, "LED turned OFF");

    while (1)
    {
        ////////////////////////////////////////////////////////////////////////////////
        //
        // Read from the SENSOR, adjust LED as appropriate (SENSOR HIGH -> LED HIGH)
        //
        if (digitalRead (SENSORpin) == HIGH)
        {
            digitalWrite (LEDpin, HIGH);
            fprintf (stdout, "\n\n\nON ");
        }

        ////////////////////////////////////////////////////////////////////////////////
        //
        // Read from the SENSOR, adjust LED as appropriate (SENSOR LOW -> LED LOW)
        //
        else
        {
            digitalWrite (LEDpin, LOW);
            fprintf (stdout, "\n\n\nOFF");
        }
    }

    return (0);
}
