//
// DHTtest.c:   test program that uses libDHT to read from two temperature sensors
// Filename:    DHT11.cpp
// Description: Read the temperature and humidity data of DHT11
//
////////////////////////////////////////////////////////////////////////////////////////

#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <DHT.h>

DHT *sensor;

int main (void)
{
    sensor                         = NULL;

    fprintf (stdout, "wiringPi / libDHT DHT11/DHT22 temperature/humidity sensor test\n");

    if (wiringPiSetup ()          == -1)
    {
        fprintf (stderr, "[ERROR] Could not initialize wiringPi\n");
        exit (1);
    }

    DHT_init (12, SENSOR_TYPE_DHT11);

    while (1)
    {
        sensor -> read ();

        if (sensor -> cached      == TRUE)
        {
            fprintf (stdout, "[cached] ");
        }

        fprintf (stdout, "DHT11: Humidity = %.1f %% ",    sensor -> humidity);
        fprintf (stdout, "Temperature = %.1f *C ",        sensor -> celcius);
        fprintf (stdout, "(%.1f *F)\n",                   sensor -> fahrenheit);

        delay (2000); /* wait 2 seconds before next read */
    }
    return (0);
}
