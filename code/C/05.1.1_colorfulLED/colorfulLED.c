//
// Filename   : colorfulLED.c
// Description: Random color change on RGB LED
// Components : RGB LED
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

#define  REDpin  0
#define  GRNpin  1
#define  BLUpin  2

////////////////////////////////////////////////////////////////////////////////////////
//
// Function prototypes
//
void     LEDsetup    (void);
void     LEDsetcolor (int32_t, int32_t, int32_t);

int32_t  main (void)
{
    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Declare and initialize variables
    //
    int32_t  red          = 0;
    int32_t  green        = 0;
    int32_t  blue         = 0;

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
    // Configure the RGB LED for software PWM operations
    //
    LEDsetup ();

    fprintf (stdout, "Program is starting (CTRL-c to interrupt) ...\n");

    while (1)
    {
        ////////////////////////////////////////////////////////////////////////////////
        //
        // For each of red, green, blue: obtain a pseudo-random value between 0 and
        // 100 (the configured software PWM range established)
        //
        red               = random () % 100;
        green             = random () % 100;
        blue              = random () % 100;

        ////////////////////////////////////////////////////////////////////////////////
        //
        // Set the RGB LED to the random values
        //
        LEDsetcolor (red, green, blue);

        ////////////////////////////////////////////////////////////////////////////////
        //
        // For informative feedback, display these values to the user
        //
        fprintf (stdout, "red: %d,  green: %d, blue: %d \n", red, green, blue);

        ////////////////////////////////////////////////////////////////////////////////
        //
        // Strategic delay to allow for better user perception (1000mS == 1 second)
        //
        delay (1000);
    }

    return (0);
}

////////////////////////////////////////////////////////////////////////////////////////
//
// Configure software PWM on the designated RGB LED GPIO pins, establishing the
// operational range of 0-100.
//
void LEDsetup (void)
{
    softPwmCreate (REDpin, 0, 100); // Create SoftPWM pin for red
    softPwmCreate (GRNpin, 0, 100); // Create SoftPWM pin for green
    softPwmCreate (BLUpin, 0, 100); // Create SoftPWM pin for blue
}

////////////////////////////////////////////////////////////////////////////////////////
//
// LEDsetcolor(): update the PWM values for the RGB LED.
//
void LEDsetcolor (int32_t redval, int32_t grnval, int32_t bluval)
{
    softPwmWrite (REDpin, redval);    // Set the REDpin to redval
    softPwmWrite (GRNpin, grnval);  // Set the GRNpin to grnval
    softPwmWrite (BLUpin, bluval);  // Set the BLUpin to bluval
}
