//
// Filename   : motor.c
// Description: Motor - control the motor
//              Uses simplified C port of ADCDevice library.
//
////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////
//
// Pre-processor directives
//
#include <math.h>
#include <softPwm.h>
#include <stdio.h>
#include <stdint.h>          // for C99 int32_t and int64_t types
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
int64_t map (int64_t value,    int64_t fromLow, int64_t fromHigh, int64_t toLow,
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
    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Declare local variable
    //
    int32_t  value  = 0;

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Based on the resultant value stored in `value`, determine action for motor:
    //
    // * greater than 0: turn forward
    // * less than 0: turn backward
    // * equal to 0: stop
    //
    ////////////////////////////////////////////////////////////////////////////////////
    
    ////////////////////////////////////////////////////////////////////////////////////
    //
    // `value` stores an ADC-provided value (0-255) adjusted to straddle the
    // zero position; its effective range will be: -128 through +127
    //
    value           = ADCvalue - 128;

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // An ADC adjusted value greater than 0 will turn the motor forward ...
    //
    if (value      >  0)
    {
        digitalWrite (motorPin1, HIGH);
        digitalWrite (motorPin2, LOW);
        fprintf (stdout, "[MOTOR] Turning Forward ...\n");
    }

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // ... and ADC adjusted value less than 0 will turn the motor backward ...
    //
    else if (value <  0)
    {
        digitalWrite (motorPin1, LOW);
        digitalWrite (motorPin2, HIGH);
        fprintf (stdout, "[MOTOR] Turning Backward ...\n");
    }

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // ... whereas a value of 0 will be associated with stopping the motor
    //
    else
    {
        digitalWrite (motorPin1, LOW);
        digitalWrite (motorPin2, LOW);
        fprintf (stdout, "[MOTOR] Stopped.\n");
    }

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Regardless of the direction, the magnitude of the value is written, determining
    // the overall motor speed (0-128), mapped to our software PWM levels of 0-100
    //
    softPwmWrite (enablePin, map (abs (value), 0, 128, 0, 100));
    fprintf (stdout, "The PWM duty cycle is: %d%%\n", abs (value) * 100 / 127);
}
