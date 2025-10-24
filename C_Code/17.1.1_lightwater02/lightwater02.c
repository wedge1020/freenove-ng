//
// Filename   : lightwater02.c
// Description: Control LED by 74HC595
//
////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////
//
// Pre-processor directives: include wiringPi and other needed header files (like the
// wiringShift.h file), along with establishing useful defines.
//
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <wiringShift.h>

#define  dataPin   0   // DS Pin of 74HC595 (Pin14)
#define  latchPin  2   // ST_CP Pin of 74HC595 (Pin12)
#define  clockPin  3   // CH_CP Pin of 74HC595 (Pin11)

////////////////////////////////////////////////////////////////////////////////////////
//
// Function prototypes
//
void _shiftOut (int32_t, int32_t, int32_t, int32_t);

int32_t  main (void)
{
    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Declare and initialize variables
    //
    int32_t  index        = 0;
    uint8_t  x            = 0;

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
    // Initialize 74HC595 pins for operation
    //
    pinMode (dataPin,  OUTPUT);
    pinMode (latchPin, OUTPUT);
    pinMode (clockPin, OUTPUT);

    fprintf (stdout, "Program is starting (CTRL-c to interrupt) ...\n");

    while (1)
    {
        x                 = 0x01;
        for (index = 0; index < 8; index++)
        {
            digitalWrite (latchPin, LOW);               // Output low level to latchPin
            _shiftOut (dataPin, clockPin, LSBFIRST, x); // Send serial data to 74HC595
            digitalWrite (latchPin, HIGH);              // Output high level to latchPin, and 74HC595 will update the data to the parallel output port.
            x             = x << 1;                     // make the variable move one bit to left once, then the bright LED move one step to the left once.
            delay (100);
        }

        x                 = 0x80;
        for (index = 0; index < 8; index++)
        {
            digitalWrite (latchPin, LOW);
            _shiftOut (dataPin, clockPin, LSBFIRST, x);
            digitalWrite (latchPin, HIGH);
            x             = x >> 1;
            delay (100);
        }
    }

    return (0);
}

////////////////////////////////////////////////////////////////////////////////////////
//
// _shiftOut(): push the data out in the intended order
//
void _shiftOut (int32_t dPin, int32_t cPin, int32_t order, int32_t val)
{
    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Declare and initialize local variables
    //
    int32_t  index     = 0;
    int32_t  state     = 0;
    int32_t  value     = 0;

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // 8 bits in the transactional byte, process for each
    //
    for (index = 0; index < 8; index++)
    {
        ////////////////////////////////////////////////////////////////////////////////
        //
        // LSB is first
        //
        if (order     == LSBFIRST)
        {
            ////////////////////////////////////////////////////////////////////////////
            //
            // Determine the state (HIGH or LOW) we will be writing for this bit of
            // the byte transaction
            //
            value      = 0x01 & (val >> index);
            if (value == 0x01)
            {
                state  = HIGH;
            }
            else
            {
                state  = LOW;
            }
        }

        ////////////////////////////////////////////////////////////////////////////////
        //
        // MSB is first
        //
        else
        {
            ////////////////////////////////////////////////////////////////////////////
            //
            // Determine the state (HIGH or LOW) we will be writing for this bit of
            // the byte transaction
            //
            value      = 0x80 & (val << index);
            if (value == 0x80)
            {
                state  = HIGH;
            }
            else
            {
                state  = LOW;
            }
        }

        ////////////////////////////////////////////////////////////////////////////////
        //
        // Perform the transaction (write the desired `state` to the bus, as
        // determined from byte order logic above
        //
        digitalWrite (cPin, LOW);
        digitalWrite (dPin, state);
        delayMicroseconds (10);
        digitalWrite (cPin, HIGH);
        delayMicroseconds (10);
    }
}
