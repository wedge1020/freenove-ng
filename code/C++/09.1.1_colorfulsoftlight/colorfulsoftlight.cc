//
// Filename:    colorfulsoftlight.cc
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

int32_t  main (void)
{
    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Declare and initialize variables
    //
    ADCDevice *adc       = NULL;
    int32_t  redval  = 0;
    int32_t  grnval  = 0;
    int32_t  bluval  = 0;

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Initialize the ADCDevice library
    //
    adc                  = new ADCDevice ();

    // Detect the pcf8591.
    if (adc -> detectI2C (0x48))
    {
        delete adc;                       // Free previously pointed memory
        adc              = new PCF8591(); // if detected, create an instance of PCF8591
    }
    // Detect the ads7830
    else if (adc -> detectI2C (0x4b))
    {
        delete adc;                       // Free previously pointed memory
        adc              = new ADS7830(); // If detected, create an instance of ADS7830
    }
    else
    {
    // Prompts error message if I2C address undetected
        fprintf (stderr, "No correct I2C address found, \n"
        "Please use command 'i2cdetect -y 1' to check the I2C address! \n"
        "Program Exit. \n");
        exit (1);
    }

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
