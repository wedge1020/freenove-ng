//
// Filename   : steppingmotor.c
// Description: Drive stepping Motor
//
////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////
//
// Preprocessor directives
//
#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>

////////////////////////////////////////////////////////////////////////////////////////
//
// Declare and initialize global variables related to motor and rotational motions
//
int32_t motor[]    = {   1,    4,    5,    6}; // phase ABCD of stepper motor
int32_t CCWStep[]  = {0x01, 0x02, 0x04, 0x08}; // coil rotation counter-clockwise
int32_t CWStep[]   = {0x08, 0x04, 0x02, 0x01}; // coil rotation clockwise

////////////////////////////////////////////////////////////////////////////////////////
//
// Function prototypes
//
void moveOnePeriod (int32_t, int32_t);
void moveSteps     (int32_t, int32_t, int32_t);
void motorStop     (void);

int32_t main (void)
{
    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Declare and initialize local variables
    //
    int32_t  index        = 0;

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
    // Initialize all 4 pins of the motor to OUTPUT mode
    //
    for(index = 0; index < 4; index++)
    {
        pinMode (motor[index], OUTPUT);
    }

    fprintf (stdout, "Program is starting (CTRL-c to interrupt) ...\n");

    while (1)
    {
        ////////////////////////////////////////////////////////////////////////////////
        //
        // Rotate the motor 360 degrees clockwise (2048 steps, 512 cycles)
        //
        moveSteps (1, 3, 512);
        delay (500);

        ////////////////////////////////////////////////////////////////////////////////
        //
        // Rotate the motor 360 degrees counter-clockwise
        //
        moveSteps (0, 3, 512);
        delay (500);
    }

    return (0);
}

////////////////////////////////////////////////////////////////////////////////////////
//
// moveOnePeriod(): drive the stepper motor (a four phase motor) one full rotation
//                  (the for steps as established)
//
void moveOnePeriod (int32_t  direction, int32_t  ms)
{
    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Declare and initialize iteration variables
    //
    int32_t phase                   = 0;
    int32_t pin                     = 0;
    int32_t position                = 0;
    int32_t value                   = 0;

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Cycle motor according to power supply order
    //
    for (phase = 0; phase < 4; phase++)
    {
        ////////////////////////////////////////////////////////////////////////////////
        //
        // Reference each pin of the motor
        //
        for (pin = 0; pin < 4; pin++)
        {
            ////////////////////////////////////////////////////////////////////////////
            //
            // Obtain the pin bit position offset (to compare against the stepping
            // position)
            //
            position                = (1 << pin);

            ////////////////////////////////////////////////////////////////////////////
            //
            // Clockwise motion
            //
            if (direction          == 1)
            {
                ////////////////////////////////////////////////////////////////////////
                //
                // Determine if the current phase matches the pin position offset;
                // set value appropriately
                //
                if (CCWStep[phase] == position)
                {
                    value           = HIGH;
                }
                else
                {
                    value           = LOW;
                }
            }

            ////////////////////////////////////////////////////////////////////////////
            //
            // Counter-clockwise motion
            //
            else
            {
                ////////////////////////////////////////////////////////////////////////
                //
                // Determine if the current phase matches the pin position offset;
                // set value appropriately
                //
                if (CWStep[phase]  == position)
                {
                    value           = HIGH;
                }
                else
                {
                    value           = LOW;
                }
            }

            ////////////////////////////////////////////////////////////////////////////
            //
            // Adjust the motor
            //
            digitalWrite (motor[pin], value);

            ////////////////////////////////////////////////////////////////////////////
            //
            // Read the motor pin
            //
            value                   = digitalRead (motor[pin]);

            ////////////////////////////////////////////////////////////////////////////
            //
            // Display the state of variables in the current transaction
            //
            fprintf (stdout, "motor[%d]: %d, %d\n", pin, motor[pin], value);
        }

        fprintf (stdout, "[motor] Step cycle complete!\n");

        ////////////////////////////////////////////////////////////////////////////////
        //
        // The delay cannot be less than 3mS, otherwise it will exceed the operational
        // speed limit of the motor
        //
        if (ms                     <  3)
        {
            ms                      = 3;
        }
        delay (ms);
    }
}

////////////////////////////////////////////////////////////////////////////////////////
//
// moveSteps(): rotate in direction, with indicated delay (in mS), cycles times
//
void moveSteps (int32_t  direction, int32_t  ms, int32_t  cycles)
{
    int32_t index  = 0;
    for (index = 0; index < cycles; index++)
    {
        moveOnePeriod (direction, ms);
    }
}

////////////////////////////////////////////////////////////////////////////////////////
//
// motorStop(): ensure motor is not rotating
//
void motorStop (void)
{
    int32_t index  = 0;
    for (index = 0; index < 4; index++)
    {
        digitalWrite (motor[index], LOW);
    }
}
