//
// Filename    : Relay.c
// Description : Control Motor with Button and Relay 
// Author      : www.freenove.com
// modification: 2025/10/21
//
////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////
//
// Preprocessor directives: include headers and define symbols
//
#include <wiringPi.h>
#include <stdio.h>

#define  relayPin  0                     // define the relayPin
#define  buttonPin 1                     // define the buttonPin

typedef  signed long int sli;

int main (void)
{
    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Declare and initialize variables
    //
    int buttonState              = HIGH; // store the state of button
    int duration                 = 0;    // duration of state change
    int lastbuttonState          = HIGH; // store the lastState of button
    int reading                  = 0;    // button state
    int relayState               = LOW;  // store the state of relay
    sli captureTime              = 50;   // set the button state stable time
    sli lastChangeTime           = 0;    // store the change time of button state

    wiringPiSetup ();    
    
    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Configure button and relay
    //
    pinMode (relayPin, OUTPUT); 
    pinMode (buttonPin, INPUT);
    pullUpDnControl (buttonPin, PUD_UP); // pull up to high level

    fprintf (stdout, "Program is starting (CTRL-c to interrupt) ...\n");

    while (1)
    {
        ////////////////////////////////////////////////////////////////////////////////
        //
        // Read the button: if the state has changed, record the time (in an offset
        //                  of milliseconds) of change
        //
        reading                  = digitalRead (buttonPin);
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

        digitalWrite (relayPin, relayState);
        lastbuttonState          = reading;
    }

    return (0);
}

