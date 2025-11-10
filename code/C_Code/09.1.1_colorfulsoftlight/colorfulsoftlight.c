//
// Filename   : colorfulsoftlight.c
// Description: Use ADC module to read the voltage value of potentiometer.
//              Uses simplified C port of ADCDevice library.
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

#define  REDLED   3     // define 3 pins for RGBLED, set to wiringpi pin #'s
#define  GRNLED   2
#define  BLULED   0

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
    softPwmCreate (REDLED, 0, 100);
    softPwmCreate (GRNLED, 0, 100);
    softPwmCreate (BLULED, 0, 100);

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
        softPwmWrite (REDLED, redval * 100 / 255);
        softPwmWrite (GRNLED, grnval * 100 / 255);
        softPwmWrite (BLULED, bluval * 100 / 255);

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
