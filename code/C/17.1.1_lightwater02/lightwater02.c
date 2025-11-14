//
// Filename:    lightwater02.c
// Description: Control LED by 74HC595
// Components:  LED, 74HC595
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

#define  DATApin   0   // DS Pin of 74HC595 (Pin14)
#define  LATCHpin  2   // ST_CP Pin of 74HC595 (Pin12)
#define  CLOCKpin  3   // CH_CP Pin of 74HC595 (Pin11)

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
    pinMode (DATApin,  OUTPUT);
    pinMode (LATCHpin, OUTPUT);
    pinMode (CLOCKpin, OUTPUT);

    fprintf (stdout, "Program is starting (CTRL-c to interrupt) ...\n");

    while (1)
    {
        x                 = 0x01;
        for (index = 0; index < 8; index++)
        {
            ////////////////////////////////////////////////////////////////////////////
            //
            // Start the transaction by resetting LATCHpin LOW
            //
            digitalWrite (LATCHpin, LOW);

            ////////////////////////////////////////////////////////////////////////////
            //
            // Call the wiringShift.h function shiftOut to send serial data to the
            // 74HC595
            //
            shiftOut (DATApin, CLOCKpin, LSBFIRST, x);

            ////////////////////////////////////////////////////////////////////////////
            //
            // Complete the current transaction by setting LATCHpin HIGH
            //
            digitalWrite (LATCHpin, HIGH);

            ////////////////////////////////////////////////////////////////////////////
            //
            // Adjust to the next bit position
            //
            x             = x << 1;
            delay (100);
        }

        x                 = 0x80;
        for (index = 0; index < 8; index++)
        {
            digitalWrite (LATCHpin, LOW);
            shiftOut (DATApin, CLOCKpin, LSBFIRST, x);
            digitalWrite (LATCHpin, HIGH);
            x             = x >> 1;
            delay (100);
        }
    }

    return (0);
}
