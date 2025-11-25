//
//  DHT.c:
//    read temperature and humidity from DHT11 or DHT22 sensor
//
////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////
//
// Pre-processor directives
//
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "DHT.h"

////////////////////////////////////////////////////////////////////////////////////////
//
// Initialize a DHT instance, associating pin with type of component
//
int32_t  DHT_init (uint8_t  pin, uint8_t  type)
{
    int32_t  len                           = 0;
    int32_t  status                        = DHTLIB_OK;

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // an existing pointer (set to NULL) is passed in; allocate
    // memory and initialize to defaults.
    //
    if (sensor                            == NULL)
    {
        sensor                             = (DHT *) malloc (sizeof (DHT));
        if (sensor                        == NULL)
        {
            fprintf (stderr, "[DHT] ERROR allocating memory for DHT instance\n");
            exit (1);
        }

        ////////////////////////////////////////////////////////////////////////////////
        //
        // Establish default values for DHT attributes
        //
        sensor -> cached                   = FALSE;
        sensor -> celcius                  = 0.0;
        sensor -> fahrenheit               = 0.0;
        sensor -> humidity                 = 0.0;
        sensor -> checksum                 = &(sensor -> byte[4]);
        sensor -> gpio_pin                 = pin;
        sensor -> type                     = type;

        ////////////////////////////////////////////////////////////////////////////////
        //
        // DHT11:
        //
        // Before reading the data, we signal the sensor to initiate a data stream.
        // This process involves pulling the pin up and down for prescribed times,
        // requiring three distinct states for specified amounts of time:
        //
        // 1. pull pin up for 10 milliseconds (10000 microseconds)
        // 2. pull pin down for 18 milliseconds (18000 microseconds)
        // 3. pull pin up for 40 microseconds
        // 4. sensor pull pin down for 80 microseconds
        // 5. Sensor pulls pin up for 80 microseconds
        //
        // After which, make sure the pin is placed in INPUT mode for reading, as
        // actual transmission begins
        //
        ////////////////////////////////////////////////////////////////////////////////

        ////////////////////////////////////////////////////////////////////////////////
        //
        // Establish signal protocol for DHT11 sensor
        //
        if (sensor -> type                == SENSOR_TYPE_DHT11)
        {
            sensor -> pulses               = 3;

            len                            = sizeof (Pulse) * sensor -> pulses;
            sensor -> signal               = (Pulse *) malloc (len);
            if (sensor -> signal          == NULL)
            {
                fprintf (stderr, "[DHT] ERROR allocating memory for DHT pulse\n");
                exit (2);
            }

            sensor -> signal[0].timing    = 10000;
            sensor -> signal[0].state     = HIGH;
            sensor -> signal[1].timing    = 18000;
            sensor -> signal[1].state     = LOW;
            sensor -> signal[2].timing    = 40;
            sensor -> signal[2].state     = HIGH;
        }

        ////////////////////////////////////////////////////////////////////////////////
        //
        // DHT22:
        //
        // Before reading the data, we signal the sensor to initiate a data stream.
        // This process involves pulling the pin up and down for prescribed times,
        // requiring two distinct states for specified amounts of time:
        //
        // 1. host pulls pin down for at least 1 millisecond (1000 microseconds)
        // 2. host pulls pin up for 20-40 microseconds
        // 3. sensor pull pin down for 80 microseconds
        // 4. Sensor pulls pin up for 80 microseconds
        //
        // After which, data transmission commences.
        //
        ////////////////////////////////////////////////////////////////////////////////

        ////////////////////////////////////////////////////////////////////////////////
        //
        // Establish signal protocol for DHT22 sensor
        //
        else
        {
            sensor -> pulses               = 3;

            len                            = sizeof (Pulse) * sensor -> pulses;
            sensor -> signal               = (Pulse *) malloc (len);
            if (sensor -> signal          == NULL)
            {
                fprintf (stderr, "[DHT] ERROR allocating memory for DHT pulse\n");
                exit (2);
            }

            sensor -> signal[0].timing     = 1;
            sensor -> signal[0].state      = HIGH;
            sensor -> signal[1].timing     = 2000;
            sensor -> signal[1].state      = LOW;
            sensor -> signal[2].timing     = 30;
            sensor -> signal[2].state      = HIGH;
        }

        sensor -> read                     = &DHT_read;
        status                             = DHTLIB_OK;
    }
    else
    {
        fprintf (stderr, "[DHT] ERROR: DHT instance already exists (no action)\n");
        status                             = DHTLIB_ERROR_ALLOC;
    }

    return (status);
}

////////////////////////////////////////////////////////////////////////////////////////
//
// DHT_read(): function to prime the sensor and read in the data bits.
//
// DHTxx Single-bus serial data format (40 bits, 5 total bytes, takes ~4ms).
//
// byte 0: whole number humidity data (integral)
// byte 1: decimal value humidity data (decimal)
// byte 2: whole number temperature data (integral)
// byte 3: decimal value temperature data (decimal)
// byte 4: checksum of first four bytes
//
// The complete data tranmission is 40-bits. Higher order bits sent first.
//
int32_t  DHT_read (void)
{
    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Declare and initialize pertinent variables
    //
    int32_t   index                         = 0;
    int32_t   status                        = 0;
    uint8_t   bit                           = 0;
    uint8_t   checksum                      = 0;
    uint8_t   counter                       = 0;
    uint8_t   currentstate                  = HIGH;
    uint8_t   decimal                       = 0;
    uint16_t  integral                      = 0;
    uint16_t  laststate                     = HIGH;

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Initialize the sensor's byte array containing the raw sensor data
    //
    for (index = 0; index < 5; index++)
    {
        sensor -> byte[index]               = 0;
    }

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Initiate a pulse sequence to enable a data read
    //
    pinMode (sensor -> gpio_pin, OUTPUT);
    for (index = 0; index < sensor -> pulses; index++)
    {
        digitalWrite (sensor      -> gpio_pin, sensor -> signal[index].state);
        delayMicroseconds (sensor -> signal[index].timing);
    }

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Prepare to read the pin (switch to input mode)
    //
    digitalWrite (sensor -> gpio_pin, LOW);
    pinMode (sensor      -> gpio_pin, INPUT);

    /////////////////////////////////read code start
    /*
    // Read data from sensor.
    for(index = 0; (index < MAX_TIMINGS) && (uSec < 255); index++)
    {
        clock_gettime (CLOCK_REALTIME, &st);
        currentstate                      = digitalRead ((*sensor) -> gpio_pin);
        while ((currentstate             == laststate) &&
               (uSec                     <  255) )
        {
            clock_gettime (CLOCK_REALTIME, &cur);
            uSec                          = ((cur.tv_sec - st.tv_sec) * 1000000); // elapsed microsecs
            uSec                          = usec + ((cur.tv_nsec - st.tv_nsec) / 1000); // elapsed microsecs
            currentstate                  = digitalRead ((*sensor) -> gpio_pin);
        }

        laststate                         = digitalRead ((*sensor) -> gpio_pin);

        // First 2 state changes are sensor signaling ready to send, ignore them.
        // Each bit is preceeded by a state change to mark its beginning, ignore it too.
        if ((index                       >  2) &&
            ((index % 2)                 == 0))
        {
            // Each array element has 8 bits.  Shift Left 1 bit.
            (*sensor) -> byte[bit/8]      = (*sensor) -> byte[bit/8] << 1;
            // A State Change > 35 µS is a '1'.
            if(uSec                      >  35)
            {
                (*sensor) -> byte[bit/8]  = (*sensor) -> byte[bit/8] | 0x00000001;
            }

            bit                           = bit + 1;
        }
    }
    /////////////////////////////////read code stop
    */
    
    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Detect any change and read in the data
    //
    for (index = 0; index <  MAX_TIMINGS; index++)
    {
        counter                             = 0;
        currentstate                        = digitalRead (sensor -> gpio_pin);
        while ((currentstate               == laststate) &&
               (counter                    != 255))
        {
            delayMicroseconds (1);
            currentstate                    = digitalRead (sensor -> gpio_pin);
            counter                         = counter + 1;
        }

        laststate                           = digitalRead (sensor -> gpio_pin);

        if (counter                        == 255)
        {
            break;
        }

        ////////////////////////////////////////////////////////////////////////////////
        //
        // Per device specifications, ignore the initial 3 transitions, and then only
        // process every other even state obtained
        //
        if ((index                         >= 4) &&
            ((index % 2)                   == 0))
        {
            ////////////////////////////////////////////////////////////////////////////
            //
            // Store each validly-obtained bit into position in the current element
            // of the sensor's byte array
            //
            sensor -> byte[bit / 8]         = sensor -> byte[bit / 8] << 1;

            if (counter                    >  16)
            {
                sensor -> byte[bit / 8]     = sensor -> byte[bit / 8] | 1;
            }

            ////////////////////////////////////////////////////////////////////////////
            //
            // This constitutes a successful bit retrieved, out of the 40-bits in the
            // payload
            //
            bit                             = bit + 1;
        }
    }

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Calculate the checksum of the data stored in our array (add first four data
    // bytes together, bitwise AND by 0xFF).
    //
    checksum                       = 0;
    for (index = 0; index < 4; index++)
    {
        checksum                   = checksum + sensor -> byte[index];
    }

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Check that we read 40 bits (8bit x 5) + verify checksum in the last byte;
    // if a match, display the sensor information.
    //
    if ((bit                      >= 40) &&
        ((*sensor -> checksum)    == checksum))
    {
        ////////////////////////////////////////////////////////////////////////////////
        //
        // HUMIDITY: Obtain integral and decimal bytes and determine the value
        //
        integral                   = sensor  -> byte[0] << 8;
        decimal                    = (sensor -> byte[1]) / 10;
        sensor -> humidity         = (float) (integral + decimal);

        ////////////////////////////////////////////////////////////////////////////////
        //
        // HUMIDITY: DHT11 compensation
        //
        if (sensor -> humidity    >  100)
        {
            sensor -> humidity     = sensor -> byte[0];
        }

        ////////////////////////////////////////////////////////////////////////////////
        //
        // TEMPERATURE: Obtain integral and decimal bytes and determine the value;
        //              units of celcius.
        //
        integral                   = ((sensor -> byte[2]) & 0x7F) << 8;
        decimal                    = (sensor  -> byte[3]) / 10;
        sensor -> celcius          = (float) (integral + decimal);

        ////////////////////////////////////////////////////////////////////////////////
        //
        // TEMPERATURE: DHT11 compensation
        //
        if (sensor -> celcius     >  125)
        {
            sensor -> celcius      = sensor -> byte[2];
        }

        ////////////////////////////////////////////////////////////////////////////////
        //
        // TEMPERATURE: Check and compensation for values below 0C; should only
        //              impact the DHT22
        //
        if (sensor -> byte[2] & 0x80)
        {
            sensor -> celcius      = sensor -> celcius * -1;
        }

        ////////////////////////////////////////////////////////////////////////////////
        //
        // TEMPERATURE: Convert from celcius to fahrenheit
        //
        sensor -> fahrenheit       = sensor -> celcius * 1.8f + 32;

        ////////////////////////////////////////////////////////////////////////////////
        //
        // CACHED: This was considered a successful read, so there is no need to rely
        //         on cached data from a previous run.
        //
        sensor -> cached           = FALSE;
        status                     = DHTLIB_OK;
    }

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Read attempt failed: proceed with existing, cached data
    //
    else
    {
        ////////////////////////////////////////////////////////////////////////////////
        //
        // CACHED: The read attempt fell through, utilize existing, cached data.
        //
        sensor -> cached           = TRUE;
        status                     = DHTLIB_ERROR_CHECKSUM;
    }

    return (status);
}
