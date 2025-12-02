//
// Filename:    ADCDevice.h
// Description: Cleaned version of C++ Header file of Freenove ADC Module library.
//
////////////////////////////////////////////////////////////////////////////////////////

#ifndef _ADCDEVICE_H
#define _ADCDEVICE_H

////////////////////////////////////////////////////////////////////////////////////////
//
// Pre-processor directives
//
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>

////////////////////////////////////////////////////////////////////////////////////////
//
// ADCDevice class
//
struct ADCDevice
{
    ////////////////////////////////////////////////////////////////////////////////////
    //
    // ADCDevice attributes
    //
    protected:
        int32_t  _fd;
    public:
        int32_t  address;
        int32_t  cmd;

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // ADCDevice functions
    //
                          ADCDevice ();                 //Costructor
        virtual          ~ADCDevice ();                 //Destructor
        virtual  int  analogRead (int chn);
                 int  detectI2C  (int32_t addr);
};

////////////////////////////////////////////////////////////////////////////////////////
//
// PCF8591 class
//
struct PCF8591:public ADCDevice
{
    ////////////////////////////////////////////////////////////////////////////////////
    //
    // PCF8591functions
    //
    public:
            PCF8591     (int addr = 0x48);    // constructor
        int analogRead  (int chn);            // has 4 ADC input pins, chn:0,1,2,3
        int analogWrite (int value);          // has DAC function
};

////////////////////////////////////////////////////////////////////////////////////////
//
// ADS7830 class
//
struct ADS7830:public ADCDevice
{
    ////////////////////////////////////////////////////////////////////////////////////
    //
    // PCF8591 functions
    //
    public:
            ADS7830     (int addr = 0x4B);    // constructor
        int analogRead  (int chn);            // has 8 ADC inputs, chn: 0-7
};



#endif

