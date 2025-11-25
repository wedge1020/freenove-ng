//
// Filename:    DHT.c
// Description: Read the temperature and humidity data of DHT11
//
////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////
//
// Pre-processor directives
//
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <wiringPi.h>
#include <DHT.h>

#define  DHTpin  5

////////////////////////////////////////////////////////////////////////////////////////
//
// global sensor instance
//
DHT *sensor;

int main (void)
{
    ////////////////////////////////////////////////////////////////////////////////////
    //
    // initialize variables
    //
    sensor                         = NULL;

    fprintf (stdout, "wiringPi / libDHT DHT11/DHT22 temperature/humidity sensor test\n");

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // initialize wiringPi
    //
    if (wiringPiSetup ()          == -1)
    {
        fprintf (stderr, "[ERROR] Could not initialize wiringPi\n");
        exit (1);
    }

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // initialize wiringPi
    //
    DHT_init (DHTpin, SENSOR_TYPE_DHT11);

    while (1)
    {
        ////////////////////////////////////////////////////////////////////////////////
        //
        // perform a sensor read
        //
        sensor -> read ();

        ////////////////////////////////////////////////////////////////////////////////
        //
        // determine if the read was successful, if not, reference cached data
        //
        if (sensor -> cached      == TRUE)
        {
            fprintf (stdout, "[cached] ");
        }

        ////////////////////////////////////////////////////////////////////////////////
        //
        // display humidity and temperature read from the sensor
        //
        fprintf (stdout, "DHT11: Humidity = %.1f %% ",    sensor -> humidity);
        fprintf (stdout, "Temperature = %.1f *C ",        sensor -> celcius);
        fprintf (stdout, "(%.1f *F)\n",                   sensor -> fahrenheit);

        ////////////////////////////////////////////////////////////////////////////////
        //
        // specifications require at least 2 seconds between reads
        //
        delay (2000);
    }

    return (0);
}
