//
// Filename:    ADCDevice.h
// Description: C version of C++ Header file of Freenove ADC Module library.
//              Simplified version using global variable.
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
// ADCDevice struct
//
struct ADCdevice
{
    ////////////////////////////////////////////////////////////////////////////////////
    //
    // ADCDevice attributes
    //
    int32_t  _fd;
    int32_t  address;
    int32_t  cmd;

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // ADCDevice function pointers
    //
    int32_t  (*analogRead)       (int32_t);
    int32_t  (*analogWrite)      (int32_t);
    int32_t  (*detectI2C)        (int32_t);
};
typedef struct ADCdevice ADCDevice;

////////////////////////////////////////////////////////////////////////////////////////
//
// Declare global ADCDevice variable
//
extern ADCDevice *adc;

////////////////////////////////////////////////////////////////////////////////////////
//
// function prototypes
//
int32_t      init_ADCDevice      ();
int32_t      ADCDevice_detectI2C (int32_t);
int32_t      PCF8591_analogRead  (int32_t); // has 4 ADC input pins, chn: 0-3
int32_t      PCF8591_analogWrite (int32_t); // has DAC function
int32_t      ADS7830_analogRead  (int32_t); // has 8 ADC inputs, chn: 0-7

#endif
