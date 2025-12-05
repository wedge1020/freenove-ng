//
// Filename:    softlight.cc
// Description: Use potentiometer to control LED
// NOTE:        needs ADCDevice library from code/C/libraries/ADCDevice
// Components:  ADC module, potentiometer, LED
//
////////////////////////////////////////////////////////////////////////////////////////

// Pre-processor directives
#include <wiringPi.h>
#include <softPwm.h>
#include <iostream>
#include <cstdint>
#include <ADCDevice.h>

#define  LEDpin 0

// Declare Global ADCDevice variable
ADCDevice   *adc;

int32_t  main (void)
{
    // Declare and initialize variables
    int32_t  ADCvalue    = 0;
    float    voltage     = 0.0;

    // Initialize the ADCDevice library
    adc                  = NULL;
    init_ADCDevice ();

    // Create software PWM control for LED
    softPwmCreate (LEDpin, 0, 100);

    std::cout << "Program is starting (CTRL-c to interrupt) ..." << std::endl;

    // Main loop: proceed indefinitely until interruption
    while (1)
    {
        ADCvalue         = adc -> analogRead (0);          // read value of A0 pin
        softPwmWrite (LEDpin, ADCvalue * 100 / 255);       // Mapping to PWM duty cycle
        voltage          = (float) ADCvalue / 255.0 * 3.3; // Calculate voltage
        std::cout << "ADC value: " << ADCvalue << ", Voltage: " << voltage << "V" << std::endl;
        delay (30);
    }

    return (0);
}
