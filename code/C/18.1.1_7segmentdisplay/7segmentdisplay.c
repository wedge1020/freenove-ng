//
// Filename:    7segmentdisplay.c
// Description: Control SevenSegmentDisplay by 74HC595
// Components:  74HC595, 7 segment display
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
        for (index = 0; index < sizeof (num); index++)
        {
            ////////////////////////////////////////////////////////////////////////////
            //
            // Output the values in num[]
            //
            digitalWrite (LATCHpin, LOW);
            shiftOut (DATApin, CLOCKpin, MSBFIRST, num[index]);
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
            shiftOut (DATApin, CLOCKpin, MSBFIRST, num[index] & 0x7f);
            digitalWrite (LATCHpin, HIGH);
            delay (500);
        }
    }
    return (0);
}
