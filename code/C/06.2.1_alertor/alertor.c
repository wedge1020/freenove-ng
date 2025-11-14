//
// Filename:    alertor.c
// Description: Make Alertor with BUZZER and BUTTON
// Components:  BUTTON, BUZZER
//
////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////
//
// Pre-processor directives: include header files for wiringPi and math libraries,
// define symbols for easier reference to our utilized wiringPi GPIOs
//
#include <math.h>
#include <softTone.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <wiringPi.h>

#define  BUTTONpin     1      // define the BUTTONpin
#define  BUZZERpin     0      // define the BUZZERpin

////////////////////////////////////////////////////////////////////////////////////////
//
// Function prototypes for buzzer operation
//
void     alertor     (int32_t);
void     stopAlertor (int32_t);

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
    // Set pin modes for involved wiringPi GPIO pins, and configure button and buzzer
    //
    pinMode (BUTTONpin, INPUT);
    pinMode (BUZZERpin, OUTPUT);
    softToneCreate (BUZZERpin);           // set BUZZERpin for tone generation
    pullUpDnControl (BUTTONpin, PUD_UP);  // pull up to HIGH level

    fprintf (stdout, "Program is starting (CTRL-c to interrupt) ...\n");
    fprintf (stdout, "[ALERTOR] turned OFF");

    while (1)
    {
        ////////////////////////////////////////////////////////////////////////////////
        //
        // Button is pressed, generate alert using buzzer
        //
        if (digitalRead (BUTTONpin) == LOW)
        {
            alertor (BUZZERpin);
            fprintf (stdout, "\b\b\bON ");
        }

        ////////////////////////////////////////////////////////////////////////////////
        //
        // Button is released, quiet the buzzer
        //
        else
        {
            stopAlertor (BUZZERpin);
            fprintf (stdout, "\b\b\bOFF");
        }
    }

    return (0);
}

////////////////////////////////////////////////////////////////////////////////////////
//
// Generate an alert from the buzzer on indicated pin
//
void alertor (int32_t  pin)
{
    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Declare and initialize variables
    //
    int32_t  x        = 0;
    double   sinVal   = 0.0;
    double   toneVal  = 0.0;

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Calculate and generate tone, utilizing the sine function
    //
    for (x = 0; x < 360; x++)
    {
        sinVal        = sin (x * (M_PI / 180)); // Calculate the sine value
        toneVal       = 2000 + sinVal * 500;    // Add frequency, weighted sine value
        softToneWrite (pin, toneVal);          // output corresponding PWM
        delay (1);
    }
}

////////////////////////////////////////////////////////////////////////////////////////
//
// Quiet the buzzer on indicated wiringPi GPIO pin
//
void stopAlertor (int32_t  pin)
{
    softToneWrite (pin, 0);
}
