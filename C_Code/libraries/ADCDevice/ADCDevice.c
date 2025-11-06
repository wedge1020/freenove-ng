//
// Filename:    ADCDevice.c
// Description: C conversion of Freenove ADC Module library (C++)
//              Simplified version using a global variable.
//
////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////
//
// Pre-processor directives
//
#include "ADCDevice.h"

////////////////////////////////////////////////////////////////////////////////////////
//
// Initialize the ADCDevice library
//
int32_t  init_ADCDevice ()
{
    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Declare and initialize variables
    //
    int32_t  status         = 1;

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Initialize wiringPi library
    //
    if (wiringPiSetup ()   == 0)
    {
        ////////////////////////////////////////////////////////////////////////////////
        //
        // Set status to SUCCESS
        //
        status              = 0;

        ////////////////////////////////////////////////////////////////////////////////
        //
        // Allocate memory and assign defaults
        //
        adc                 = (ADCDevice *) malloc (sizeof (ADCDevice));
        adc -> address      = 0;
        adc -> detectI2C    = &ADCDevice_detectI2C;

        ////////////////////////////////////////////////////////////////////////////////
        //
        // ADC chip detection: PCF8591
        //
        if (adc -> detectI2C (0x48))
        {
            ////////////////////////////////////////////////////////////////////////////
            //
            // Initialize ADCDevice attributes to PCF8591 settings
            //
            adc -> address      = 0x48;
            adc -> cmd          = 0x40; // The default command for PCF8591 is 0x40

            ////////////////////////////////////////////////////////////////////////////
            //
            // Establish analogRead and analogWrite functions per detected ADC module
            //
            adc -> analogRead   = &PCF8591_analogRead;
            adc -> analogWrite  = &PCF8591_analogWrite;

            fprintf (stdout, "[ADCDevice] PCF8591 setup successful!\n");
        }
        ////////////////////////////////////////////////////////////////////////////////
        //
        // ADC chip detection: ADS7830
        //
        else if (adc -> detectI2C (0x4b))
        {
            ////////////////////////////////////////////////////////////////////////////
            //
            // Initialize ADCDevice attributes to ADS7830 settings
            //
            adc -> address      = 0x4b;
            adc -> cmd          = 0x84;

            ////////////////////////////////////////////////////////////////////////////
            //
            // Establish analogRead and analogWrite functions per detected ADC module
            //
            adc -> analogRead   = &ADS7830_analogRead;
            adc -> analogWrite  = NULL;

            fprintf (stdout, "[ADCDevice] ADS7830 setup successful!\n");
        }

        ////////////////////////////////////////////////////////////////////////////////
        //
        // ADC chip detection: neither module detected
        //
        else
        {
            fprintf (stderr, "[ERROR] No correct I2C address found!\n");
            fprintf (stderr,          "Please use the command 'i2cdetect -y 1' ");
            fprintf (stderr,          "to check the I2C address!\n");
            exit (1);
        }
    }
    else
    {
        fprintf (stderr, "[ERROR] wiringPi initialization failed!\n");
        exit (2);
    }

    return (status);
}

////////////////////////////////////////////////////////////////////////////////////////
//
// Attempt to detect which ADC module is in use
//
int32_t  ADCDevice_detectI2C (int32_t  addr)
{
    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Declare and initialize variables
    //
    int32_t  _fd                       = 0;
    int32_t  status                    = 0;

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Initialize wiringPi I2C subsystem
    //
    adc -> _fd                         = wiringPiI2CSetup (addr);   
    _fd                                = adc -> _fd;

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Check for failure of initializing wiringPi I2C subsystem
    //
    if (_fd                           <  0)
    {        
        fprintf (stderr, "[ERROR] address: 0x%x \n", addr);
        status                         = 0;
    } 

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Subsystem may have initialized, check for additional failure or success states
    //
    else
    {
        ////////////////////////////////////////////////////////////////////////////////
        //
        // Attempt writing to the device, checking for a failure
        //
        if (wiringPiI2CWrite (_fd, 0) <  0)
        {
            fprintf (stderr, "[ERROR] device not found at address 0x%x \n", addr);
            status                     = 0;
        }

        ////////////////////////////////////////////////////////////////////////////////
        //
        // If writing to the device was successful, we have our module
        //
        else
        {
            fprintf (stdout, "[ADCDevice] Found device at address 0x%x \n", addr);
            status                     = 1;
        }
    }

    return (status);
}

////////////////////////////////////////////////////////////////////////////////////////
//
// a PCF8591-compatible analogRead function (to be used with ADCDevice function
// pointer).
//
int32_t  PCF8591_analogRead (int32_t  chn)
{
    wiringPiI2CWrite (adc -> _fd, (adc -> cmd + chn));
    wiringPiI2CRead  (adc -> _fd);
    wiringPiI2CWrite (adc -> _fd, (adc -> cmd + chn));
    return (wiringPiI2CRead (adc -> _fd));
}

////////////////////////////////////////////////////////////////////////////////////////
//
// a PCF8591-compatible analogWrite function (to be used with ADCDevice function
// pointer).
//
int32_t  PCF8591_analogWrite (int32_t  value)
{
    return (wiringPiI2CWriteReg8 (adc -> _fd, adc -> cmd, value));
}

////////////////////////////////////////////////////////////////////////////////////////
//
// a ADS7830-compatible analogRead function (to be used with ADCDevice function
// pointer).
//
int32_t  ADS7830_analogRead (int32_t  chn)
{
    wiringPiI2CWrite (adc -> _fd, adc -> cmd | (((chn << 2 | chn >> 1) & 0x07) << 4));
    return (wiringPiI2CRead (adc -> _fd));
}
