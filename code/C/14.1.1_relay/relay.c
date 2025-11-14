//
// Filename:    relay.c
// Description: Control Motor with Button and Relay
// Components:  Motor, Relay, Button
//
////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////
//
// Preprocessor directives: include headers and define symbols
//
#include <stdio.h>
#include <stdint.h>                      // for C99 int32_t and int64_t types
#include <stdlib.h>
#include <wiringPi.h>

#define  BUTTONpin 1                     // define the BUTTONpin
#define  RELAYpin  0                     // define the RELAYpin

int32_t  main (void)
{
    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Declare and initialize variables
    //
    int32_t  buttonState         = HIGH; // store the state of button
    int32_t  duration            = 0;    // duration of state change
    int32_t  lastbuttonState     = HIGH; // store the lastState of button
    int32_t  reading             = 0;    // button state
    int32_t  relayState          = LOW;  // store the state of relay
    int64_t  captureTime         = 50;   // set the button state stable time
    int64_t  lastChangeTime      = 0;    // store the change time of button state

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Bring wiringPi functionality online
    //
    if (wiringPiSetup ()        == -1)
    {
        fprintf (stderr, "[ERROR] Could not initialize wiringPi library!\n");
        exit (1);
    }

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Configure button and relay
    //
    pinMode (RELAYpin, OUTPUT);
    pinMode (BUTTONpin, INPUT);
    pullUpDnControl (BUTTONpin, PUD_UP); // pull up to high level

    fprintf (stdout, "Program is starting (CTRL-c to interrupt) ...\n");

    while (1)
    {
        ////////////////////////////////////////////////////////////////////////////////
        //
        // Read the button: if the state has changed, record the time (in an offset
        //                  of milliseconds) of change
        //
        reading                  = digitalRead (BUTTONpin);
        if (reading             != lastbuttonState)
        {
            lastChangeTime       = millis ();
        }

        ////////////////////////////////////////////////////////////////////////////////
        //
        // Check if we have passed a reasonable threshold of time to trigger a
        // button press
        //
        duration                 = millis () - lastChangeTime;
        if (duration            >  captureTime)
        {
            ////////////////////////////////////////////////////////////////////////////
            //
            // If button state is changed, update the data
            //
            if (reading         != buttonState)
            {
                buttonState      = reading;

                ////////////////////////////////////////////////////////////////////////
                //
                // A low button state indicates pressing
                //
                if (buttonState == LOW)
                {
                    fprintf (stdout, "[BUTTON] pressed!\n");
                    relayState   = !relayState;
                    if (relayState)
                    {
                        fprintf (stdout, "[RELAY] turned on ...\n");
                    }
                    else
                    {
                        fprintf (stdout, "[RELAY] turned off ...\n");
                    }
                }

                ////////////////////////////////////////////////////////////////////////
                //
                // A high button state indicates releasing
                //
                else
                {
                    fprintf (stdout, "[BUTTON] released!\n");
                }
            }
        }

        digitalWrite (RELAYpin, relayState);
        lastbuttonState          = reading;
    }

    return (0);
}

