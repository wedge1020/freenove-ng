/***
 *** Filename    : adc.c
 *** Description : Use ADC module to read the voltage value of potentiometer.
 ***               Uses simplified C port of ADCDevice library.
 *** Modification: 2025/09/28    
 ***
 **************************************************************************************/
        
#include <wiringPi.h>
#include <stdio.h>
#include <ADCDevice.h>
        
int main (void)
{       
    ////////////////////////////////////////////////////////////////////////////////////
    //  
    // Declare and initialize variables
    //  
    int        adcValue  = 0;
    float      voltage   = 0.0;

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
        adcValue  = adc -> analogRead (0);          // read analog value of A0 pin
        voltage   = (float) adcValue / 255.0 * 3.3; // Calculate voltage
        fprintf (stdout, "ADC value: %3d, Voltage:   %.2fV\n", adcValue, voltage);
        delay (100);
    }

    return (0);
}
