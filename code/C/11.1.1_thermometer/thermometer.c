//
// Filename:    thermometer.c
// Description: DIY Thermometer
// NOTE:        needs ADCDevice library from code/C/libraries/ADCDevice
//
////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////
//
// Pre-processor directives
//
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include <wiringPi.h>
#include <ADCDevice.h>

////////////////////////////////////////////////////////////////////////////////////////
//
// Declare Global ADCDevice variable
//
ADCDevice *adc;

int32_t  main (void)
{
    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Declare and initialize variables
    //
    int32_t    ADCvalue  = 0;
    float      voltage   = 0.0;
    float      rt        = 0.0;
    float      tempK     = 0.0;
    float      tempC     = 0.0;

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Initialize the ADCDevice library
    //
    adc                  = NULL;
    init_ADCDevice ();

    fprintf (stdout, "Program is starting (CTRL-c to interrupt) ...\n");

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Main loop: proceed indefinitely until interruption
    //
    while (1)
    {
        ADCvalue         = adc -> analogRead (0);          // read value of A0 pin
        voltage          = (float) ADCvalue / 255.0 * 3.3; // Calculate voltage
        rt               = 10 * voltage / (3.3 - voltage); // Thermister resistance
        tempK            = 1 / (1 / (273.15 + 25) + log (rt / 10) / 3950.0);
        tempC            = tempK - 273.15;                 // Calculate Celsius
        fprintf (stdout, "ADC value: %3d, Voltage: %.2fV ", ADCvalue, voltage);
        fprintf (stdout, "Temperature: %.2fC\n", tempC);
        delay (100);
    }

    return (0);
}
