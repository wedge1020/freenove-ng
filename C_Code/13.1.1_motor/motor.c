//
// Filename    : motor.c
// Description : Motor - control the motor
//               Uses simplified C port of ADCDevice library.
// Modification: 2025/10/21
//
////////////////////////////////////////////////////////////////////////////////////////

#include <math.h>
#include <softPwm.h>
#include <stdint.h>          // for C99 int32_t and int64_t types
#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <ADCDevice.h>

#define  motorPin1  2        // the wiringPi pin connected to L293D
#define  motorPin2  0
#define  enablePin  3

////////////////////////////////////////////////////////////////////////////////////////
//
// Global ADCDevice variable
//
ADCDevice *adc;
        
////////////////////////////////////////////////////////////////////////////////////////
//
// Function prototypes
//
int64_t  map   (int64_t, int64_t, int64_t, int64_t, int64_t);
void     motor (int32_t);

int32_t main (void)
{       
    ////////////////////////////////////////////////////////////////////////////////////
    //  
    // Declare and initialize variables
    //  
    int32_t  value       = 0;

    ////////////////////////////////////////////////////////////////////////////////////
    //  
    // Initialize the ADCDevice library
    //
    adc                  = NULL;
    init_ADCDevice ();

    ////////////////////////////////////////////////////////////////////////////////////
    //  
    // Set pin modes and create a software PWM pin 
    //
    pinMode (enablePin, OUTPUT);
    pinMode (motorPin1, OUTPUT);
    pinMode (motorPin2, OUTPUT);
    softPwmCreate (enablePin, 0, 100);

    fprintf (stdout, "Program is starting (CTRL-c to interrupt) ...\n");

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Main loop: proceed indefinitely until interruption
    //
    while (1)
    {
        value            = adc -> analogRead (0);          // read value of A0 pin
        fprintf (stdout, "ADC value: %3d\n", value);
        motor (value);
        delay (100);
    }

    return (0);
}

////////////////////////////////////////////////////////////////////////////////////////
//
// Map function: map the value from a range to another range.
//
int64_t map (int64_t value,    int64_t fromLow,
             int64_t fromHigh, int64_t toLow,
             int64_t toHigh)
{
    return ((toHigh - toLow) * (value - fromLow) / (fromHigh - fromLow) + toLow);
}

////////////////////////////////////////////////////////////////////////////////////////
//
// Motor function: determine the direction and speed of the motor according to the ADC 
//
void motor (int32_t ADCvalue)
{
    int32_t  value  = 0;

    value           = ADCvalue - 128;
    if (value      >  0)
    {
        digitalWrite (motorPin1, HIGH);
        digitalWrite (motorPin2, LOW);
        fprintf (stdout, "[MOTOR] Turning Forward ...\n");
    }
    else if (value <  0)
    {
        digitalWrite (motorPin1, LOW);
        digitalWrite (motorPin2, HIGH);
        fprintf (stdout, "[MOTOR] Turning Backward ...\n");
    }
    else
    {
        digitalWrite (motorPin1, LOW); 
        digitalWrite (motorPin2, LOW);
        fprintf (stdout, "[MOTOR] Stopped.\n");
    }

    softPwmWrite (enablePin, map (abs (value), 0, 128, 0, 100));
    fprintf (stdout, "The PWM duty cycle is: %d%%\n", abs (value) * 100 / 127);
}
