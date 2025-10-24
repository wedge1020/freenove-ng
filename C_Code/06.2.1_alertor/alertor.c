//
// Filename   : alertor.c
// Description: Make Alertor with buzzer and button.
//
////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////
//
// Preprocessor directives: include header files for wiringPi and math libraries,
// define symbols for easier reference to our utilized wiringPi GPIOs
//
#include <math.h>
#include <softTone.h>
#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>

#define  buttonPin     1      // define the buttonPin
#define  buzzerPin     0      // define the buzzerPin

////////////////////////////////////////////////////////////////////////////////////////
//
// Function prototypes for buzzer operation
//
void alertor     (int);
void stopAlertor (int);

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
    // Set pin modes for involved wiringPi GPIO pins, and configure button and buzzer
    //
    pinMode (buttonPin, INPUT);
    pinMode (buzzerPin, OUTPUT);
    softToneCreate (buzzerPin);           // set buzzerPin for tone generation
    pullUpDnControl (buttonPin, PUD_UP);  // pull up to HIGH level

    fprintf (stdout, "Program is starting (CTRL-c to interrupt) ...\n");
    fprintf (stdout, "[ALERTOR] turned OFF");

    while (1)
    {
        ////////////////////////////////////////////////////////////////////////////////
        //
        // Button is pressed, generate alert using buzzer
        //
        if (digitalRead (buttonPin) == LOW)
        {
            alertor (buzzerPin);
            fprintf (stdout, "\b\b\bON ");
        }

        ////////////////////////////////////////////////////////////////////////////////
        //
        // Button is released, quiet the buzzer
        //
        else
        {
            stopAlertor (buzzerPin);
            fprintf (stdout, "\b\b\bOFF");
        }
    }

    return (0);
}

////////////////////////////////////////////////////////////////////////////////////////
//
// Generate an alert from the buzzer on indicated pin
//
void alertor (int pin)
{
    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Declare and initialize variables
    //
    int     x        = 0;
    double  sinVal   = 0.0;
    double  toneVal  = 0.0;

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Calculate and generate tone, utilizing the sine function
    //
    for (x = 0; x < 360; x++)
    {
        sinVal       = sin (x * (M_PI / 180)); // Calculate the sine value
        toneVal      = 2000 + sinVal * 500;    // Add frequency, weighted sine value
        softToneWrite (pin, toneVal);          // output corresponding PWM
        delay (1);
    }
}

////////////////////////////////////////////////////////////////////////////////////////
//
// Quiet the buzzer on indicated wiringPi GPIO pin
//
void stopAlertor (int pin)
{
    softToneWrite (pin,0);
}

