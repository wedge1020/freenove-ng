/***
 *** Filename    : nightlamp.c
 *** Description : Nightlamp - use photoresistor to control LED.
 ***               Uses simplified C port of ADCDevice library.
 *** Modification: 2025/09/28    
 ***
 **************************************************************************************/
        
#include <wiringPi.h>
#include <softPwm.h>
#include <stdio.h>
#include <ADCDevice.h>

#define  ledPin 0
        
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

    ////////////////////////////////////////////////////////////////////////////////////
    //  
    // Create software PWM control for LED
    //
    softPwmCreate (ledPin, 0, 100);

    fprintf (stdout, "Program is starting (CTRL-c to interrupt) ...\n");

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Main loop: proceed indefinitely until interruption
    //
    while (1)
    {
        adcValue         = adc -> analogRead (0);          // read value of A0 pin
        softPwmWrite (ledPin, adcValue * 100 / 255);       // Mapping to PWM duty cycle
        voltage          = (float) adcValue / 255.0 * 3.3; // Calculate voltage
        fprintf (stdout, "ADC value: %3d, Voltage: %.2fV\n", adcValue, voltage);
        delay (100);
    }

    return (0);
}
