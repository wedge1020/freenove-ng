//
// Filename:    tablelamp.cc
// Description: DIY MINI table lamp
// Components:  LED, BUTTON
//
////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////
//
// Pre-processor directives
//
#include <iostream>
#include <stdint.h>
#include <wiringPi.h>

#define  LEDpin     0  // GPIO wiringPi pin for the LED
#define  BUTTONpin  1  // GPIO wiringPi pin for the BUTTON

int32_t  main (void)
{
    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Declare and initialize variables
    //
    int32_t  LEDstate             = LOW;   // stores the current state of the LED
    int32_t  BUTTONstate          = HIGH;  // store the current state of the BUTTON
    int32_t  lastBUTTONstate      = HIGH;  // store the last state of the BUTTON
    int64_t  lastChangeTime       = 0;     // store the change time of BUTTON state
    int64_t  captureTime          = 50;    // set the stable time for BUTTON state
    int32_t  reading              = 0;

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Bring wiringPi functionality online
    //
    if (wiringPiSetup ()         == -1)
    {
        std::cout << "[ERROR] Could not initialize wiringPi library" << std::endl;
        exit (1);
    }

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // configure the peripheral pins for the appropriate modes of operation
    //
    pinMode (LEDpin,    OUTPUT);          // LED is an output component (we write it)
    pinMode (BUTTONpin, INPUT);           // BUTTON is an input component (we read it)
    pullUpDnControl (BUTTONpin, PUD_UP);  // pull up to high level

    std::cout << "Program is starting (CTRL-c to interrupt) ..." << std::endl;

    while (1)
    {
        ////////////////////////////////////////////////////////////////////////////////
        //
        // read the current state of the BUTTON; if its state has changed, record
        // the time
        //
        reading                   = digitalRead (BUTTONpin);
        if (reading              != lastBUTTONstate)
        {
            lastChangeTime        = millis ();
        }

        ////////////////////////////////////////////////////////////////////////////////
        //
        // if the BUTTON state change exceeds timing threshold, treat it like a
        // fresh press
        //
        if (captureTime          <  millis () - lastChangeTime)
        {
            ////////////////////////////////////////////////////////////////////////////
            //
            // if BUTTON state has changed, update the data
            //
            if (reading          != BUTTONstate)
            {
                ////////////////////////////////////////////////////////////////////////
                //
                // if BUTTON state is LOW, it is being pressed
                //
                BUTTONstate       = reading;
                if (BUTTONstate  == LOW)
                {
                    ////////////////////////////////////////////////////////////////////
                    //
                    // reverse the LED state, and then report to user
                    //
                    std::cout << "[BUTTON] PRESSED" << std::endl;

                    LEDstate      = !LEDstate;
                    if (LEDstate == HIGH)
                    {
                        fprintf (stdout, "[LED] turn ON  ...\n");
                    }
                    else
                    {
                        fprintf (stdout, "[LED] turn OFF ...\n");
                    }
                }

                ////////////////////////////////////////////////////////////////////////
                //
                // else BUTTON state is LOW, it is NOT being pressed
                //
                else
                {
                    std::cout << "[BUTTON] RELEASED" << std::endl;
                }
            }
        }

        ////////////////////////////////////////////////////////////////////////////////
        //
        // update LED output to its current logical state
        //
        digitalWrite (LEDpin, LEDstate);

        ////////////////////////////////////////////////////////////////////////////////
        //
        // update the historical BUTTON state information to match last reading
        //
        lastBUTTONstate           = reading;
    }

    return (0);
}
