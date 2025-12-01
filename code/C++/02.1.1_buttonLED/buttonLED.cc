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
#include <iostream>
#include <wiringPi.h>
#include <cstdint>

#define  LEDpin     0      // GPIO wiringPi pin for LED component
#define  BUTTONpin  1    // GPIO wiringPi pin for BUTTON component

int32_t  main (void)
{
    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Bring wiringPi functionality online
    //
    if (wiringPiSetup ()         == -1)
    {
        std::cout << "[ERROR] Could not initialize wiringPi library!" << std::endl; 
        exit (1);
    }

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // configure the peripheral pins for the appropriate modes of operation
    //
    pinMode (LEDpin,    OUTPUT);          // LED is an output component (we write it)
    pinMode (BUTTONpin, INPUT);           // BUTTON is an input component (we read it)
    pullUpDnControl (BUTTONpin, PUD_UP);  // pull up to HIGH level

    std::cout << "Program is starting (CTRL-c to interupt) ..." << std::endl;

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Display the default status (note the lack of newline at the end, so that with
    // the strategic use of backspaces, we can update this line in place)
    //
    std::cout << " BUTTON: released, LED: OFF" << std::endl;

    while (1)
    {
        ////////////////////////////////////////////////////////////////////////////////
        //
        // on LOW signal read, BUTTON is pressed
        //
        if (digitalRead (BUTTONpin) == LOW)
        {
            digitalWrite (LEDpin, HIGH);  // turn the LED on
            //fprintf (stdout, "\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\bpressed,  LED: ON ");
        }

        ////////////////////////////////////////////////////////////////////////////////
        //
        // on HIGH signal read, BUTTON is released
        //
        else
        {
            digitalWrite (LEDpin, LOW);   // turn the LED off
            //fprintf (stdout, "\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\breleased, LED: OFF");
        }
    }

    return (0);
}
