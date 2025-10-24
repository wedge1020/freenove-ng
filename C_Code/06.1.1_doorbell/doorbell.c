//
// Filename   : doorbell.c
// Description: Make doorbell with buzzer and button.
//
////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////
//
// Preprocessor directives: include wiringPi, define symbols
//
#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>

#define  buttonPin 1    // define the buttonPin
#define  buzzerPin 0    // define the buzzerPin

int main (void)
{
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
    // Set pin modes for involved wiringPi GPIO pins, and configure button
    //
    pinMode (buttonPin, INPUT);
    pinMode (buzzerPin, OUTPUT);
    pullUpDnControl (buttonPin, PUD_UP);  // pull up to HIGH level

    fprintf (stdout, "Program is starting (CTRL-c to interrupt) ...\n");
    fprintf (stdout, "[BUZZER] turned OFF");

    while (1)
    {
        ////////////////////////////////////////////////////////////////////////////////
        //
        // Button is pressed, turn on buzzer
        //
        if (digitalRead (buttonPin) == LOW)
        {
            digitalWrite (buzzerPin, HIGH);
            fprintf (stdout, "\b\b\bON ");
        }

        ////////////////////////////////////////////////////////////////////////////////
        //
        // Button is released, turn off buzzer
        //
        else
        {
            digitalWrite (buzzerPin, LOW);
            fprintf (stdout, "\b\b\bOFF");
        }
    }

    return (0);
}
