//
// Filename:    lightwater03.c
// Description: Control LED with 74HC595 on DIY circuit board
//
////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////
//
// Pre-processor directives
//
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <wiringPi.h>
#include <wiringShift.h>

#define  DATApin    0   // DS Pin of 74HC595    (pin 14)
#define  LATCHpin   2   // ST_CP Pin of 74HC595 (pin 12)
#define  CLOCKpin   3   // SH_CP Pin of 74HC595 (pin 11)

////////////////////////////////////////////////////////////////////////////////////////
//
// function prototypes
//
void     outData (int8_t);

int32_t  main (void)
{
    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Declare and initialize variables
    //
    int8_t   data          = 0;   // amassed data
    int32_t  cycle         = 0;   // cycle within the 64 cycle PWM
    int32_t  position      = 0;   // LED position (0-7)
    int32_t  offset        = 0;   // current position in pulsewidth array
    int32_t  moveSpeed     = 100; // a delay; larger values slow it down
    int64_t  lastMove      = 0;   // stores time of last move operation
    int64_t  snapshot      = 0;

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Define an  array to store  the pulse width  of LED, which  will be
    // output to the 8 LEDs in order.
    //
    int32_t  pulsewidth[]  = { 0,  0,  0,  0,
                               0,  0,  0,  0,
                               64, 32, 16, 8,
                               4,  2,  1,  0,
                               0,  0,  0,  0,
                               0,  0,  0 };

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Bring wiringPi functionality online
    //
    if (wiringPiSetup ()  == -1)
    {
        fprintf (stderr, "[ERROR] Could not initialize wiringPi library!\n");
        exit (1);
    }

    fprintf (stdout, "Program is starting (CTRL-c to interrupt) ...\n\n");

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Configure 74HC595 pins
    //
    pinMode (DATApin,  OUTPUT);
    pinMode (LATCHpin, OUTPUT);
    pinMode (CLOCKpin, OUTPUT);

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Starting at array offset 0
    //
    offset                 = 0;

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Record the starting time
    //
    lastMove               = millis ();

    while (1)
    {
        ////////////////////////////////////////////////////////////////////////////////
        //
        // Speed check/control
        //
        snapshot           = millis () - lastMove;
        if (snapshot      >  moveSpeed)
        {
            ////////////////////////////////////////////////////////////////////////////
            //
            // Record the time the move transaction took place
            //
            lastMove       = millis ();    //Record the time point of the move

            ////////////////////////////////////////////////////////////////////////////
            //
            // Advance offset within pulsewidth array, keeping bounded within a range
            //
            offset         = offset + 1;
            if (offset    >  15)
            {
                offset     = 0;
            }
        }

        ////////////////////////////////////////////////////////////////////////////////
        //
        // PWM is 64 cycles
        //
        for (cycle         = 0;
             cycle        <  64;
             cycle         = cycle + 1)
        {
            ////////////////////////////////////////////////////////////////////////////
            //
            // LED position (out of 8)
            //
            data           = 0;
            for (position  = 0;
                 position <  8;
                 position  = position + 1)
            {
                ////////////////////////////////////////////////////////////////////////
                //
                // Calculate the LED state according to the pulse width
                //
                if (cycle <  pulsewidth[offset + position])
                {
                    data   = data | 0x01 << position;
                }
            }

            ////////////////////////////////////////////////////////////////////////////
            //
            // Send the data to the 74HC595
            //
            outData (data);
        }
    }

    return (0);
}

void     outData (int8_t  data)
{
    digitalWrite (LATCHpin, LOW);
    shiftOut     (DATApin,  CLOCKpin, LSBFIRST, data);
    digitalWrite (LATCHpin, HIGH);
}
