//
// Filename:    ADCDevice.cc
// Description: Cleaned up version of Freenove ADC Module library (C++)
//
////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////
//
// Pre-processor directives
//
#include "ADCDevice.h"

////////////////////////////////////////////////////////////////////////////////////////
//
// ADCDevice constructor
//
ADCDevice::ADCDevice(){
    address = 0;
    wiringPiSetup();
}

////////////////////////////////////////////////////////////////////////////////////////
//
// Attempt to detect which ADC module is in use
//
int ADCDevice::detectI2C(int  addr)
{
    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Initialize wiringPi I2C subsystem
    //
    _fd                              = wiringPiI2CSetup (addr);

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Check for failure of initializing wiringPi I2C subsystem
    //
    if (_fd                         <  0)
    {
        printf("Error address : 0x%x \n",addr);
        return 0;
    }
    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Attempt writing to the device, checking for a failure
    //
    else if(wiringPiI2CWrite(_fd,0) <  0)
    {
        printf("Not found device in address 0x%x \n",addr);
        return 0;

    }
    ////////////////////////////////////////////////////////////////////////////////////
    //
    // If writing to the device was successful, we have our module
    //
    else
    {
        printf("Found device in address 0x%x \n",addr);
        return 1;
    }
}

////////////////////////////////////////////////////////////////////////////////////////
//
// PCF8591 constructor
//
PCF8591::PCF8591(int addr)
{
    ////////////////////////////////////////////////////////////////////////////
    //
    // Initialize ADCDevice attributes to PCF8591 settings
    //
    address = addr;
    cmd     = 0x40; //The default command for PCF8591 is 0x40.


    ////////////////////////////////////////////////////////////////////////////
    //
    // Establish analogRead and analogWrite functions per detected ADC module
    //
    wiringPiSetup();
    detectI2C(address);

    printf("PCF8591 setup successful! \n");
}

////////////////////////////////////////////////////////////////////////////////////////
//
// a PCF8591-specific analogRead function
//
int  PCF8591::analogRead (int  chn)
{
    wiringPiI2CWrite (_fd, cmd + chn);
    wiringPiI2CRead  (_fd);
    wiringPiI2CWrite (_fd, cmd + chn);
    return (wiringPiI2CRead (_fd));
}

////////////////////////////////////////////////////////////////////////////////////////
//
// a PCF8591-specific analogWrite function
//
int  PCF8591::analogWrite (int  value)
{
    return (wiringPiI2CWriteReg8 (_fd, cmd, value));
}

////////////////////////////////////////////////////////////////////////////////////////
//
// ADS7830 constructor
//
ADS7830::ADS7830(int addr)
{
    ////////////////////////////////////////////////////////////////////////////
    //
    // Initialize ADCDevice attributes to ADS7830 settings
    //
    address = addr;
    cmd     = 0x84; //The default command for is ADS7830 0x40.


    ////////////////////////////////////////////////////////////////////////////
    //
    // Establish analogRead and analogWrite functions per detected ADC module
    //
    wiringPiSetup();
    detectI2C(address);

    printf("ADS7830 setup successful! \n");
}

////////////////////////////////////////////////////////////////////////////////////////
//
// a ADS7830-specific analogRead function
//
int  ADS7830::analogRead (int  chn)
{
    wiringPiI2CWrite (_fd, cmd + chn);
    wiringPiI2CRead  (_fd);
    wiringPiI2CWrite (_fd, cmd + chn);
    return (wiringPiI2CRead (_fd));
}
