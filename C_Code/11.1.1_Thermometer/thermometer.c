/***
 *** Filename    : thermometer.c
 *** Description : DIY Thermometer
 ***               Uses simplified C port of ADCDevice library.
 *** Modification: 2025/09/28    
 ***
 **************************************************************************************/
        
#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ADCDevice.h>
        
int main (void)
{       
    ////////////////////////////////////////////////////////////////////////////////////
    //  
    // Declare and initialize variables
    //  
    int        adcValue  = 0;
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
        adcValue         = adc -> analogRead (0);          // read value of A0 pin
        voltage          = (float) adcValue / 255.0 * 3.3; // Calculate voltage
        rt               = 10 * voltage / (3.3 - voltage); // Thermister resistance
        tempK            = 1 / (1 / (273.15 + 25) + log (rt / 10) / 3950.0);
        tempC            = tempK - 273.15;                 // Calculate Celsius
        fprintf (stdout, "ADC value: %3d, Voltage: %.2fV ", adcValue, voltage);
        fprintf (stdout, "Temperature: %.2fC\n", tempC);
        delay (100);
    }

    return (0);
}
