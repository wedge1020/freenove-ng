//
// Filename:    softlight.cc
// Description: Use potentiometer to control LED
// NOTE:        needs ADCDevice library from code/C++/libraries/ADCDevice
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

int32_t  main (void)
{
    // Declare and initialize variables
    ADCDevice *adc       = NULL;
    int32_t    ADCvalue  = 0;
    float      voltage   = 0.0;

    // Initialize the ADCDevice library
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
        fprintf (stderr, "No correct I2C address found, \n"
        "Please use command 'i2cdetect -y 1' to check the I2C address! \n"
        "Program Exit. \n");
        exit (1);
    } 

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
