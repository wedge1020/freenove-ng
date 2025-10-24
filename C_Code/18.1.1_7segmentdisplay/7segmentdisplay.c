//
// Filename    : SevenSegmentDisplay.c
// Description : Control SevenSegmentDisplay by 74HC595
//
////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////
//
// Pre-processor directives
//
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <wiringShift.h>

#define  DATApin   0    // DS Pin of 74HC595 (Pin14)
#define  LATCHpin  2    // ST_CP Pin of 74HC595 (Pin12)
#define  CLOCKpin  3    // CH_CP Pin of 74HC595 (Pin11)

////////////////////////////////////////////////////////////////////////////////////////
//
// Function prototypes
//
void _shiftOut (int32_t, int32_t, int32_t, int32_t);

int32_t main (void)
{
    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Declare and initialize variables
    //
    int32_t  index    = 0;

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // num[] stores the Encoding for characters 0-F of common anode 7 segment display
    //
    uint8_t  num[] = { 0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xf8,
                       0x80, 0x90, 0x88, 0x83, 0xc6, 0xa1, 0x86, 0x8e };

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
    // Set pinmodes for the 74HC595
    //
    pinMode (DATApin,  OUTPUT);
    pinMode (LATCHpin, OUTPUT);
    pinMode (CLOCKpin, OUTPUT);

    fprintf (stdout, "Program is starting (CTRL-c to interrupt) ...\n");

    while (1)
    {
        for (index = 0; i < sizeof (num); i++)
        {
            ////////////////////////////////////////////////////////////////////////////
            //
            // Output the values in num[]
            //
            digitalWrite (LATCHpin, LOW);
            _shiftOut (DATApin, CLOCKpin, MSBFIRST, num[index]);
            digitalWrite (LATCHpin, HIGH);
            delay (500);
        }

        for (index = 0; index < sizeof (num); index++)
        {
            ////////////////////////////////////////////////////////////////////////////
            //
            // Display the decimal point
            //
            digitalWrite (LATCHpin, LOW);
            _shiftOut (DATApin, CLOCKpin, MSBFIRST, num[index] & 0x7f);
            digitalWrite (LATCHpin, HIGH);
            delay (500);
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
    int32_t  bit       = 0;
    int32_t  state     = 0;
    int32_t  value     = 0;

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // 8 bits in the transactional byte, process for each
    //
    for (bit = 0; bit < 8; bit++)
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
            value      = 0x01 & (val >> bit);
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
            value      = 0x80 & (val << bit);
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
