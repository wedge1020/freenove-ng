//
// Filename:    colorfulsoftlight.c
// Description: Use ADC module to read the voltage value of potentiometer.
// NOTE:        needs ADCDevice library from code/C/libraries/ADCDevice
//
////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////
//
// Pre-processor directives
//
#include <wiringPi.h>
#include <softPwm.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <ADCDevice.h>

#define  REDpin   3     // define 3 pins for RGBpin, set to wiringpi pin #'s
#define  GRNpin   2
#define  BLUpin   0

////////////////////////////////////////////////////////////////////////////////////////
//
// Declare Global ADCDevice variable
//
ADCDevice   *adc;

int32_t  main (void)
{
    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Declare and initialize variables
    //
    int32_t  redval  = 0;
    int32_t  grnval  = 0;
    int32_t  bluval  = 0;

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Initialize the ADCDevice library
    //
    adc              = NULL;
    init_ADCDevice ();

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // PWM: set the LED pins to PWM output, standard software range (0-100)
    //
    softPwmCreate (REDpin, 0, 100);
    softPwmCreate (GRNpin, 0, 100);
    softPwmCreate (BLUpin, 0, 100);

    fprintf (stdout, "Program is starting (CTRL-c to interrupt) ...\n");

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Main loop: proceed indefinitely until interruption
    //
    while (1)
    {
        ////////////////////////////////////////////////////////////////////////////////
        //
        // Read analog value of 3 potentiometers
        //
        redval       = adc -> analogRead (0);
        grnval       = adc -> analogRead (1);
        bluval       = adc -> analogRead (2);

        ////////////////////////////////////////////////////////////////////////////////
        //
        // Map the read value of the potentiometers into PWM value and output it
        //
        softPwmWrite (REDpin, redval * 100 / 255);
        softPwmWrite (GRNpin, grnval * 100 / 255);
        softPwmWrite (BLUpin, bluval * 100 / 255);

        ////////////////////////////////////////////////////////////////////////////////
        //
        // Display the current value for each color value
        //
        fprintf (stdout, "[ADC] red: %3d, green: %3d, blue: %3d \n", redval,
                                                                     grnval,
                                                                     bluval);
        delay (100);
    }

    return (0);
}
