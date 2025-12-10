//
// Filename:    breathingLED.cc
// Description: simulate a "breathing" LED with software PWM
// Components:  LED
//
////////////////////////////////////////////////////////////////////////////////////////

// Pre-processor directives
#include <iostream>
#include <cstdint>
#include <wiringPi.h>
#include <softPwm.h>


class LED
{
public:
    LED();
    LED(int32_t bval, int pin);
    
    void breathOn();
    void breathOff();
    int32_t getPin();
private:
    // Declare and initialize variables
    int32_t level;
    int32_t LEDpin; // wiringPi GPIO pin
};

int32_t  main (void)
{

    // Bring wiringPi functionality online
    if (wiringPiSetup() == -1)
    {
        std::cout << "[ERROR] Could not intialize wiringPi library!" << std::endl;
        exit(1);
    }

    LED newLED;
    
    // Initialize LEDpin for software PWM operation, with a range from 0 to 100
    softPwmCreate(newLED.getPin(), 0, 100);


    std::cout << "Program is starting (CTRL-c to interrupt) ..." << std::endl;

    while(1)
    {
        ////////////////////////////////////////////////////////////////////////////////
        //
        // adjust the LED gradually from fully OFF (0) to fully ON (100), one step at
        // a time
        //
        newLED.breathOn();

        // strategic delay for better user perception
        delay(300);

        ////////////////////////////////////////////////////////////////////////////////
        //
        // adjust the LED gradually from fully ON (100) to fully OFF (0), one step at
        // a time
        //
        newLED.breathOff();

        // strategic delay for better user perception
        delay(300);
    }

    return (0);
}

LED::LED()
{
    level = 0;
    LEDpin = 1;
}

LED::LED(int32_t bval, int32_t pin)
{
   level = bval;
   LEDpin = pin;
}

////////////////////////////////////////////////////////////////////////////////
//
// adjust the LED gradually from fully OFF (0) to fully ON (100), one step at
// a time
//
void LED::breathOn()
{
    
    for (level = 0; level < 100; level++)
    {
        softPwmWrite(LEDpin, level);
        delay(20);
    }
}

////////////////////////////////////////////////////////////////////////////////
//
// adjust the LED gradually from fully ON (100) to fully OFF (0), one step at
// a time
//
void LED::breathOff()
{
    for (level = 100; level >= 0; level--)
    {
        softPwmWrite(LEDpin, level);
        delay(20);
    }
}

int32_t LED::getPin()
{
  return LEDpin;
}
