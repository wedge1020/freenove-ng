//
// Filename   : stopwatch.c
// Description: Control 4-Digit 7-Segment Display by 74HC595
//
////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////
//
// Pre-processor directives
//
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <wiringPi.h>
#include <wiringShift.h>

#define  DATApin     5    // DS Pin of 74HC595 (Pin14)
#define  LATCHpin    4    // ST_CP Pin of 74HC595 (Pin12)
#define  CLOCKpin    1    // CH_CP Pin of 74HC595 (Pin11)
#define  PAUSE       1

////////////////////////////////////////////////////////////////////////////////////////
//
// global variables
//
int32_t  counter;                             // the number that will be displayed
int32_t  digitPin[]  = { 0, 2, 3, 12 };       // 7-segment display wiringPi pins

////////////////////////////////////////////////////////////////////////////////////////
//
// function prototypes
//
void selectDigit (int32_t);
void shiftout    (int32_t, int32_t, int32_t, int32_t);
void outData     (int8_t);
void display     (int32_t);
void timer       (int32_t);

int32_t main (void)
{
    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Declare and initialize variables
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
    // Set pinmodes for the 74HC595
    //
    pinMode (DATApin,  OUTPUT);
    pinMode (LATCHpin, OUTPUT);
    pinMode (CLOCKpin, OUTPUT);

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // set the pin connected to 7-segment display common end to output mode
    //
    for (index = 0; index < 4; index++)
    {
        pinMode (digitPin[index], OUTPUT);
        digitalWrite (digitPin[index], HIGH);
    }

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Initialize the counter
    //
    counter               = 0;

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Configure and arm the timer, setting it to 1 second
    //
    signal (SIGALRM, timer);
    alarm (1);

    fprintf (stdout, "Program is starting (CTRL-c to interrupt) ...\n");

    while (1)
    {
        ////////////////////////////////////////////////////////////////////////////////
        //
        // Display the number counter
        //
        display (counter);
    }

    return (0);
}

////////////////////////////////////////////////////////////////////////////////////////
//
// selectDigit(): open one of the 7-segment displays and close the remaining three;
//                the parameter `digit` is optional for values of 1, 2, 4, or 8
//
void selectDigit (int32_t  digit)
{
    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Declare and initialize local variables
    //
    int32_t  bitmask           = 0;
    int32_t  offset            = 0;
    int32_t  value             = 0;

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Determine which of the 7-segment displays is selected
    //
    for (bitmask = 0x08; bitmask > 0x00; bitmask = bitmask / 2)
    {
        if ((digit & bitmask) == bitmask)
        {
            value              = LOW;
        }
        else
        {
            value              = HIGH;
        }

        digitalWrite (digitPin[offset], value);
        offset                 = offset + 1;
    }
}

////////////////////////////////////////////////////////////////////////////////////////
//
// shiftout(): push the data out in the intended order
//
void shiftout (int32_t  dPin, int32_t  cPin, int32_t  order, int32_t  val)
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

////////////////////////////////////////////////////////////////////////////////////////
//
// outData(): function used to output data to the 74HC595
//
void outData (int8_t  data)
{
    digitalWrite (LATCHpin, LOW);
    shiftout (DATApin, CLOCKpin, MSBFIRST, data);
    digitalWrite (LATCHpin, HIGH);
}

////////////////////////////////////////////////////////////////////////////////////////
//
// display(): update the 7-segment display
//
//
void display (int32_t value)
{
    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Declare and initialize pertinent variables;
    // data[] contains the 0-9 character codes for the common anode 7-segment display
    //
    uint8_t  data[]   = { 0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xf8, 0x80, 0x90};
    int32_t  place    = 10;
    int32_t  remain   = 1;
    int32_t  segment  = 0;

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Cycle through the four 7-segment displays, displaying the appropriate digit
    // in each
    //
    for (segment = 0x01; segment <= 0x08; segment = segment << 1)
    {
        outData (0xff);
        selectDigit (segment);
        outData (data[value % place / remain]);
        delay (PAUSE);
        place         = place  * 10;
        remain        = remain * 10;
    }
}

////////////////////////////////////////////////////////////////////////////////////////
//
// timer(): function fired off by SIGALRM to update the timer's counter
//
void timer (int32_t sig)
{
    ////////////////////////////////////////////////////////////////////////////////////
    //
    // only process for SIGALRM
    //
    if (sig     == SIGALRM)
    {
        ////////////////////////////////////////////////////////////////////////////////
        //
        // update the counter
        //
        counter  = counter + 1;

        ////////////////////////////////////////////////////////////////////////////////
        //
        // re-arm the timer to fire off in one second
        //
        alarm (1);

        ////////////////////////////////////////////////////////////////////////////////
        //
        // display the current count of the counter
        //
        fprintf (stdout, "[counter] %d\n", counter);
    }
}
