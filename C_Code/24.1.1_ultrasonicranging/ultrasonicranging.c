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

typedef  struct timeval TimeVal;

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
    int64_t  micros           = 0;
    TimeVal  tn;
    TimeVal  t0;
    TimeVal  t1;

    gettimeofday (&t0, NULL);

    while (digitalRead (pin) != level)
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
        if (micros           >  timeout)
        {
            return (0);
        }
    }

    gettimeofday (&t1, NULL);
    while (digitalRead (pin) == level)
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

        if (micros           >  timeout)
        {
            return (0);
        }
    }

    if (tn.tv_sec            >  t1.tv_sec)
    {
        micros                = 1000000L;
    }
    else
    {
        micros                = 0;
    }

    micros                    = micros + (tn.tv_usec - t1.tv_usec);

    return (micros);
}

////////////////////////////////////////////////////////////////////////////////////////
//
// getSonar(): get the distance measurement calculated from the sensor (in units
//             of centimeters)
//
float  getSonar ()
{
    int64_t  pingTime  = 0;
    float    distance  = 0.0;

    digitalWrite (TRIGGERpin, HIGH); //send 10us high level to TRIGGERpin

    delayMicroseconds (10);

    digitalWrite (TRIGGERpin, LOW);
    pingTime           = pulseIn (ECHOpin, HIGH, TIMEOUT);   //read plus time of ECHOpin
    distance           = (float) pingTime * 340.0 / 2.0 / 10000.0; //calculate distance with sound speed 340m/s
    return (distance);
}
