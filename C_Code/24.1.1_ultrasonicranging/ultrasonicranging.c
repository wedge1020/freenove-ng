//
// Filename:    ultrasonicranging.c
// Description: Get distance via UltrasonicRanging sensor
//
////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////
//
// Pre-processor directives
//
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <sys/time.h>
#include <wiringPi.h>

#define  TRIGGERpin   4
#define  ECHOpin      5
#define  MAX_DISTANCE 220             // define the maximum measured distance
#define  TIMEOUT      MAX_DISTANCE*60 // calculate timeout

typedef  struct timeval TimeVal;      // alias for convenience

////////////////////////////////////////////////////////////////////////////////////////
//
// function prototypes
//
int32_t  pulseIn  (int32_t, int32_t, int32_t);
float    getSonar ();

int32_t  main (void)
{
    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Declare and initialize local variables
    //
    float  distance       = 0;

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
    // Configure SENSOR pins (TRIGGER and ECHO)
    //
    pinMode (TRIGGERpin, OUTPUT);
    pinMode (ECHOpin,    INPUT);

    fprintf (stdout, "Program is starting (CTRL-c to interrupt) ...\n\n");

    while (1)
    {
        ////////////////////////////////////////////////////////////////////////////////
        //
        // Obtain the current distance calculated from sampling the SENSOR
        //
        distance          = getSonar ();

        ////////////////////////////////////////////////////////////////////////////////
        //
        // Display the recently sampled value
        //
        fprintf (stdout, "[SENSOR] distance is: %.2f cm\n", distance);

        ////////////////////////////////////////////////////////////////////////////////
        //
        // Strategic pause for user perception
        //
        delay (1000);
    }

    return (0);
}

////////////////////////////////////////////////////////////////////////////////////////
//
// pulseIn(): obtain pulse time
//
int32_t  pulseIn (int32_t  pin, int32_t  level, int32_t  timeout)
{
    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Declare and initialize local variables
    //
    int64_t  micros            = 0;
    TimeVal  tn;
    TimeVal  t0;
    TimeVal  t1;

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Obtain our initial time snapshot
    //
    gettimeofday (&t0, NULL);

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // While the sampling of the pin state doesn't match level, AND we have not yet
    // surpassed the timeout threshold
    //
    while ((digitalRead (pin) != level) &&
           (micros            <= timeout))
    {
        ////////////////////////////////////////////////////////////////////////////////
        //
        // Obtain our current time snapshot
        //
        gettimeofday (&tn, NULL);
        if (tn.tv_sec         >  t0.tv_sec)
        {
            micros             = 1000000L;
        }
        else
        {
            micros             = 0;
        }

        micros                 = micros + (tn.tv_usec - t0.tv_usec);
    }

    gettimeofday (&t1, NULL);
    while ((digitalRead (pin) != level) &&
           (micros            <= timeout))
    {
        gettimeofday (&tn, NULL);
        if (tn.tv_sec        >  t0.tv_sec)
        {
            micros            = 1000000L;
        }
        else
        {
            micros            = 0;
        }

        micros                = micros + (tn.tv_usec - t0.tv_usec);
    }

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Calculate micros
    //
    if (tn.tv_sec            >  t1.tv_sec)
    {
        micros                = 1000000L;
        micros                = micros + (tn.tv_usec - t1.tv_usec);
    }

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Check for the timeout state, and do no time calculations if so
    //
    else if (micros          >  timeout)
    {
        micros                = 0;
    }
    else
    {
        micros                = 0;
        micros                = micros + (tn.tv_usec - t1.tv_usec);
    }

    return (micros);
}

////////////////////////////////////////////////////////////////////////////////////////
//
// getSonar(): get the distance measurement calculated from the sensor (in units
//             of centimeters)
//
float  getSonar ()
{
    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Declare and initialize local variables
    //
    int64_t  pingTime  = 0;
    float    distance  = 0.0;

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Initiate a SENSOR read (send TRIGGER HIGH for 10us)
    //
    digitalWrite (TRIGGERpin, HIGH);
    delayMicroseconds (10);

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Set TRIGGER LOW and commence with the read, via the ECHO pin and time offsets
    //
    digitalWrite (TRIGGERpin, LOW);
    pingTime           = pulseIn (ECHOpin, HIGH, TIMEOUT);

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Calculate the distance (based on sound speed of 340m/s)
    //
    distance           = (float) pingTime * 340.0 / 2.0 / 10000.0;

    return (distance);
}
