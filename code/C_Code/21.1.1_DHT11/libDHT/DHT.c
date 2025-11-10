//
//  dht.c:
//    read temperature and humidity from DHT11 or DHT22 sensor
//
////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////
//
// Pre-processor directives
//
#include "DHT.h"

////////////////////////////////////////////////////////////////////////////////////////
//
// Initialize the DHT instance (sensor), associating pin with type of component
//
int32_t  DHT_init (uint8_t pin, uint8_t type)
{
    int32_t  status                = DHTLIB_OK;

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Ideal conditions: sensor exists and is currently NULL. Allocate the
    //                   memory and initialize to defaults.
    //
    if (sensor                    == NULL)
    {
        sensor                     = (DHT *) malloc (sizeof (DHT));
        if (sensor                == NULL)
        {
            fprintf (stderr, "[DHT] ERROR allocating memory for DHT instance\n");
            exit (1);
        }

        ////////////////////////////////////////////////////////////////////////////////
        //
        // Establish default values for DHT attributes
        //
        sensor -> cached           = FALSE;
        sensor -> celcius          = 0.0;
        sensor -> fahrenheit       = 0.0;
        sensor -> humidity         = 0.0;
        sensor -> checksum         = &(sensor -> byte[4]);
        sensor -> gpio_pin         = pin;
        sensor -> type             = type;
        sensor -> read             = &DHT_read;
        status                     = DHTLIB_OK;
    }
    else
    {
        fprintf (stderr, "[DHT] ERROR: DHT instance already exists (no action)\n");
        status                     = DHTLIB_ERROR_ALLOC;
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
    int32_t   index                = 0;
    int32_t   status               = 0;
    uint8_t   bit                  = 0;
    uint8_t   checksum             = 0;
    uint8_t   counter              = 0;
    uint8_t   currentstate         = HIGH;
    uint8_t   decimal              = 0;
    uint16_t  integral             = 0;
    uint16_t  laststate            = HIGH;

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Initialize the sensor's byte array containing the raw sensor data
    //
    for (index = 0; index < 5; index++)
    {
        sensor -> byte[index]      = 0;
    }

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Prime the sensor: pull pin down for 18 milliseconds
    //
    pinMode (sensor -> gpio_pin, OUTPUT);
    digitalWrite (sensor -> gpio_pin, LOW);
    delay (18);

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Prepare to read the pin (switch to input mode)
    //
    pinMode (sensor -> gpio_pin, INPUT);

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Detect any change and read in the data
    //
    for (index = 0; index <  MAX_TIMINGS; index++)
    {
        counter                    = 0;
        currentstate               = digitalRead (sensor -> gpio_pin);
        while (currentstate       == laststate)
        {
            counter                = counter + 1;
            delayMicroseconds (1);
            if (counter           == 255)
            {
                break;
            }
        }

        laststate                  = digitalRead (sensor -> gpio_pin);

        if (counter               == 255)
        {
            break;
        }

        /* ignore first 3 transitions */
        if ((index                      >= 4) &&
            ((index % 2)                == 0))
        {
            /* shove each bit into the storage bytes */
            sensor -> byte[bit / 8]      = sensor -> byte[bit / 8] << 1;

            if (counter                 >  16)
            {
                sensor -> byte[bit / 8]  = sensor -> byte[bit / 8] | 1;
            }

            bit                          = bit + 1;
        }
    }

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Calculate the checksum of the data stored in our array (add first four data
    // bytes together, bitwise AND by 0xFF).
    //
    checksum                             = 0;
    for (index = 0; index < 4; index++)
    {
        checksum                         = checksum + sensor -> byte[index];
    }

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Check that we read 40 bits (8bit x 5) + verify checksum in the last byte;
    // if a match, display the sensor information.
    //
    if ((bit                            >= 40) &&
        ((*sensor -> checksum)          == checksum))
    {
        ////////////////////////////////////////////////////////////////////////////////
        //
        // HUMIDITY: Obtain integral and decimal bytes and determine the value
        //
        integral                         = sensor  -> byte[0] << 8;
        decimal                          = (sensor -> byte[1]) / 10;
        sensor -> humidity               = (float) (integral + decimal);

        ////////////////////////////////////////////////////////////////////////////////
        //
        // HUMIDITY: DHT11 compensation
        //
        if (sensor -> humidity          >  100)
        {
            sensor -> humidity           = sensor -> byte[0];
        }

        ////////////////////////////////////////////////////////////////////////////////
        //
        // TEMPERATURE: Obtain integral and decimal bytes and determine the value;
        //              units of celcius.
        //
        integral                         = ((sensor -> byte[2]) & 0x7F) << 8;
        decimal                          = (sensor  -> byte[3]) / 10;
        sensor -> celcius                = (float) (integral + decimal);

        ////////////////////////////////////////////////////////////////////////////////
        //
        // TEMPERATURE: DHT11 compensation
        //
        if (sensor -> celcius           >  125)
        {
            sensor -> celcius            = sensor -> byte[2];
        }

        ////////////////////////////////////////////////////////////////////////////////
        //
        // TEMPERATURE: Check and compensation for values below 0C; should only
        //              impact the DHT22
        //
        if (sensor -> byte[2] & 0x80)
        {
            sensor -> celcius            = sensor -> celcius * -1;
        }

        ////////////////////////////////////////////////////////////////////////////////
        //
        // TEMPERATURE: Convert from celcius to fahrenheit
        //
        sensor -> fahrenheit             = sensor -> celcius * 1.8f + 32;

        ////////////////////////////////////////////////////////////////////////////////
        //
        // CACHED: This was considered a successful read, so there is no need to rely
        //         on cached data from a previous run.
        //
        sensor -> cached                 = FALSE;
        status                           = DHTLIB_OK;
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
        sensor -> cached                 = TRUE;
        status                           = DHTLIB_ERROR_CHECKSUM;
    }

    return (status);
}
