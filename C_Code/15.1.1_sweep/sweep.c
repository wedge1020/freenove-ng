//
// Filename    : sweep.c
// Description : Servo sweep
// Author      : www.freenove.com
// modification: 2025/10/21
//
////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////
//
// Preprocessor directives: include headers for wiringPi library, define symbols
//
#include <softPwm.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>               // for C99 int32_t and int64_t types
#include <wiringPi.h>

#define OFFSET_MS    3            // unit of servo pulse offset: 0.1ms
#define SERVO_MIN_MS 5+OFFSET_MS  // pulse duration for minimum angle of servo
#define SERVO_MAX_MS 25+OFFSET_MS // pulse duration for maximum angle of servo

#define servoPin     1            // wiringPi GPIO number connected to servo

////////////////////////////////////////////////////////////////////////////////////////
//
// Function prototypes
//
int64_t  map          (int64_t, int64_t, int64_t, int64_t, int64_t);
void     servoInit    (int32_t);
void     servoWrite   (int32_t, int32_t);
void     servoWriteMS (int32_t, int32_t);

int32_t  main (void)
{
    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Declare and initialize variables
    //
    int32_t  position     = 0;
    
    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Bring wiringPi functionality online
    //
    if (wiringPiSetup () == -1)
    {
        fprintf (stderr, "[ERROR] Could not initialize wiringPi library!\n");
        exit (1);
    }

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Initialize PWM pin of servo
    //
    servoInit (servoPin);

    fprintf (stdout, "Program is starting (CTRL-c to interrupt) ...\n");

    while (1)
    {
        ////////////////////////////////////////////////////////////////////////////////
        //
        // Make servo rotate from minimum position to maximum position, then delay
        // for half a second
        //
        for (position = SERVO_MIN_MS; position < SERVO_MAX_MS; position++)
        {
            servoWriteMS (servoPin, position);
        }
        delay (500);

        ////////////////////////////////////////////////////////////////////////////////
        //
        // Make servo rotate from maximum position to maximum position, then delay
        // for half a second
        //
        for (position = SERVO_MAX_MS; position > SERVO_MIN_MS; position--)
        {
            servoWriteMS (servoPin, position);
        }
        delay (500);
    }

    return (0);
}

////////////////////////////////////////////////////////////////////////////////////////
//
// Mapping function
//
int64_t  map (int64_t value,    int64_t fromLow,
              int64_t fromHigh, int64_t toLow,
              int64_t toHigh)
{
    return (toHigh - toLow) * (value - fromLow) / (fromHigh - fromLow) + toLow;
}

////////////////////////////////////////////////////////////////////////////////////////
//
// Initialize the servo motor wiringPi GPIO pin, using software PWM
//
void  servoInit (int32_t pin)
{
    softPwmCreate (pin, 0, 200);
}

////////////////////////////////////////////////////////////////////////////////////////
//
// Adjust the servo to a specified rotation angle (0-180)
//
void  servoWrite (int32_t pin, int32_t angle)
{
    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Bounds check: ensure we do not exceed maximum angle (reset to max)
    //
    if (angle >  180)
    {
        angle  = 180;
    }

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Bounds check: ensure we do not surpass minimum angle (reset to min)
    //
    if (angle <  0)
    {
        angle  = 0;
    }

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Bounds check: ensure we do not surpass minimum angle (reset to min)
    //
    softPwmWrite (pin, map (angle, 0, 180, SERVO_MIN_MS, SERVO_MAX_MS));   
}

////////////////////////////////////////////////////////////////////////////////////////
//
// Bounds check the servo position, set the pin to the appropriate value
//
// PWM pulse: 5-25mS
// duration:  10mS
//
void  servoWriteMS (int32_t pin, int32_t ms)
{
    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Ensure we do not exceed maximum bound (reset to maximum)
    //
    if (ms >  SERVO_MAX_MS)
    {
        ms  = SERVO_MAX_MS;
    }

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Ensure we do not surpass minimum bound (reset to minimum)
    //
    if (ms <  SERVO_MIN_MS)
    {
        ms  = SERVO_MIN_MS;
    }

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Write current value to servo pin
    //
    softPwmWrite (pin, ms);
    delay (10);
}
