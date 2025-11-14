//
// Filename:    ADC.c
// Description: Use ADC module to read the voltage value of potentiometer.
//              Uses simplified C port of ADCDevice library.
// Components:  ADC module, potentiometer
//
////////////////////////////////////////////////////////////////////////////////////////

#include <wiringPi.h>
#include <stdio.h>
#include <stdint.h>
#include <ADCDevice.h>

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
    int32_t  adcValue    = 0;
    float    voltage     = 0.0;

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
