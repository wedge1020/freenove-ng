//
// Filename:    LEDmatrix.c
// Description: Control LEDmatrix by 74HC595
// Components:  74HC595, LEDmatrix
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
#define  CLOCKpin  3    // SH_CP Pin of 74HC595 (Pin11)

int32_t  main (void)
{
    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Declare and initialize variables
    //
    int32_t  index          = 0; // i
    int32_t  refresh        = 0; // j
    int32_t  k              = 0; // k
    uint8_t  column         = 0;
    uint8_t  picture[]      = { 0x1c, 0x22, 0x51, 0x45, 0x45, 0x51, 0x22, 0x1c };

    // data of smile face
    uint8_t  data[]         = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // " "
                                0x00, 0x00, 0x3E, 0x41, 0x41, 0x3E, 0x00, 0x00, // "0"
                                0x00, 0x00, 0x21, 0x7F, 0x01, 0x00, 0x00, 0x00, // "1"
                                0x00, 0x00, 0x23, 0x45, 0x49, 0x31, 0x00, 0x00, // "2"
                                0x00, 0x00, 0x22, 0x49, 0x49, 0x36, 0x00, 0x00, // "3"
                                0x00, 0x00, 0x0E, 0x32, 0x7F, 0x02, 0x00, 0x00, // "4"
                                0x00, 0x00, 0x79, 0x49, 0x49, 0x46, 0x00, 0x00, // "5"
                                0x00, 0x00, 0x3E, 0x49, 0x49, 0x26, 0x00, 0x00, // "6"
                                0x00, 0x00, 0x60, 0x47, 0x48, 0x70, 0x00, 0x00, // "7"
                                0x00, 0x00, 0x36, 0x49, 0x49, 0x36, 0x00, 0x00, // "8"
                                0x00, 0x00, 0x32, 0x49, 0x49, 0x3E, 0x00, 0x00, // "9"
                                0x00, 0x00, 0x3F, 0x44, 0x44, 0x3F, 0x00, 0x00, // "A"
                                0x00, 0x00, 0x7F, 0x49, 0x49, 0x36, 0x00, 0x00, // "B"
                                0x00, 0x00, 0x3E, 0x41, 0x41, 0x22, 0x00, 0x00, // "C"
                                0x00, 0x00, 0x7F, 0x41, 0x41, 0x3E, 0x00, 0x00, // "D"
                                0x00, 0x00, 0x7F, 0x49, 0x49, 0x41, 0x00, 0x00, // "E"
                                0x00, 0x00, 0x7F, 0x48, 0x48, 0x40, 0x00, 0x00, // "F"
                                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Bring wiringPi functionality online
    //
    if (wiringPiSetup ()   == -1)
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
        ////////////////////////////////////////////////////////////////////////////////
        //
        // Repeat enough times to display the smiling face a period of time
        //
        for (refresh = 0; refresh < 500; refresh++)
        {
            ////////////////////////////////////////////////////////////////////////////
            //
            // for each column
            //
            column          = 0x80;
            for (index = 0; index < 8; index++)
            {
                ////////////////////////////////////////////////////////////////////////
                //
                // start a new transaction
                //
                digitalWrite (LATCHpin, LOW);

                ////////////////////////////////////////////////////////////////////////
                //
                // first shift data of line information to the first stage 74HC595
                //
                shiftOut (DATApin, CLOCKpin, MSBFIRST, picture[index]);

                ////////////////////////////////////////////////////////////////////////
                //
                // ... then shift column information to the second stage 74HC595
                //
                shiftOut (DATApin, CLOCKpin, MSBFIRST, ~column);

                ////////////////////////////////////////////////////////////////////////
                //
                // Output data of two 74HC595 transactions at the same time
                //
                digitalWrite (LATCHpin, HIGH);

                ////////////////////////////////////////////////////////////////////////
                //
                // proceed to the next column
                //
                column      = column >> 1;
                delay (1);
            }
        }

        ////////////////////////////////////////////////////////////////////////////////
        //
        // sizeof (data) is the total number of "0-F" columns
        //
        for (k = 0; k < sizeof (data) - 8; k++)
        {
            ////////////////////////////////////////////////////////////////////////////
            //
            // times of repeated displaying LEDMatrix in every frame,
            // the bigger the `refresh`, the longer the display time
            //
            for (refresh = 0; refresh < 20; refresh++)
            {
                ////////////////////////////////////////////////////////////////////////
                //
                // Set the column information to start from the first column
                //
                column       = 0x80;
                for (index = k; index < 8 + k; index++)
                {
                    digitalWrite (LATCHpin, LOW);
                    shiftOut (DATApin, CLOCKpin, MSBFIRST, data[index]);
                    shiftOut (DATApin, CLOCKpin, MSBFIRST,~column);
                    digitalWrite (LATCHpin, HIGH);
                    column  = column >> 1;
                    delay (1);
                }
            }
        }
    }

    return (0);
}
