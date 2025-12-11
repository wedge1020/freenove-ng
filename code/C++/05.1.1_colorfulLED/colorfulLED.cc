//
// Filename:    colorfulLED.cc
// Description: Random color change on RGB LED
// Components:  RGB LED
//
////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////
//
// Pre-processor directives
//
#include <cstdint>
#include <cstdlib>
#include <wiringPi.h>
#include <softPwm.h>
#include <iostream>

////////////////////////////////////////////////////////////////////////////////////////
//
// Class for storing LED data
//
class LED
{
public:
    
    ////////////////////////////////////////////////////////////////////////////////////////
    //
    // Constructors
    //
    LED();
    LED(int32_t redval, int32_t grnval, int32_t bluval, int32_t redpin, int32_t grnpin, int32_t blupin);

    ////////////////////////////////////////////////////////////////////////////////////////
    //
    // Function prototypes
    //
    void LEDsetup    (void);
    void LEDsetcolor (int32_t redval, int32_t grnval, int32_t bluval);
    
    void setRed(int32_t value);
    void setGreen(int32_t value);
    void setBlue(int32_t value);
    
    int32_t getRed();
    int32_t getGreen();
    int32_t getBlue();

private:

    ////////////////////////////////////////////////////////////////////////////////////////
    //
    // Variables for storing the LEDs rgb values and pins
    //
    int32_t  red;
    int32_t  green;
    int32_t  blue;     
    
    int32_t  REDpin;//  0
    int32_t  GRNpin;//  1
    int32_t  BLUpin;//  2
};

int32_t  main (void)
{
    
    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Instantiate the LED class
    //
    LED newLED;
    
    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Bring wiringPi functionality online
    //
    if (wiringPiSetup () == -1)
    {
        std::cerr << "[ERROR] Could not initialize wiringPi library!\n";
        exit (1);
    }

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Configure the RGB LED for software PWM operations
    //
    newLED.LEDsetup ();

    std::cout << "Program is starting (CTRL-c to interrupt) ...\n";

    while (1)
    {
        ////////////////////////////////////////////////////////////////////////////////
        //
        // For each of red, green, blue: obtain a pseudo-random value between 0 and
        // 100 (the configured software PWM range established)
        //
        newLED.setRed(random () % 100);
        newLED.setGreen(random () % 100);
        newLED.setBlue(random () % 100);

        ////////////////////////////////////////////////////////////////////////////////
        //
        // Set the RGB LED to the random values
        //
        newLED.LEDsetcolor (newLED.getRed(), newLED.getGreen(), newLED.getBlue());

        ////////////////////////////////////////////////////////////////////////////////
        //
        // For informative feedback, display these values to the user
        //
        std::cout << "red: " << newLED.getRed() << ", green: " << newLED.getGreen() << ", blue: " << newLED.getBlue() << "\n";

        ////////////////////////////////////////////////////////////////////////////////
        //
        // Strategic delay to allow for better user perception (1000mS == 1 second)
        //
        delay (1000);
    }

    return (0);
}

////////////////////////////////////////////////////////////////////////////////////////
//
// LED::LED(): the parameterless constructor, initialize the member attributes to 
// default values
//
LED::LED()
{
    red = 0;
    green = 0;
    blue = 0;
    REDpin = 0;
    GRNpin = 1;
    BLUpin = 2;
}

////////////////////////////////////////////////////////////////////////////////////////
//
// LED::LED(redval, grnval, bluval, redpin, grnpin, blupin): the parametered constructor, 
// initialize the member attributes to provided values
//
LED::LED(int32_t redval, int32_t grnval, int32_t bluval, int32_t redpin, int32_t grnpin, int32_t blupin)
{
    red = redval;
    green = grnval;
    blue = bluval;
    REDpin = redpin;
    GRNpin = grnpin;
    BLUpin = blupin;
}

////////////////////////////////////////////////////////////////////////////////////////
//
// Configure software PWM on the designated RGB LED GPIO pins, establishing the
// operational range of 0-100.
//
void LED::LEDsetup (void)
{
    softPwmCreate (REDpin, 0, 100); // Create SoftPWM pin for red
    softPwmCreate (GRNpin, 0, 100); // Create SoftPWM pin for green
    softPwmCreate (BLUpin, 0, 100); // Create SoftPWM pin for blue
}

////////////////////////////////////////////////////////////////////////////////////////
//
// LEDsetcolor(): update the PWM values for the RGB LED.
//
void LED::LEDsetcolor (int32_t redval, int32_t grnval, int32_t bluval)
{
    softPwmWrite (REDpin, redval);    // Set the REDpin to redval
    softPwmWrite (GRNpin, grnval);  // Set the GRNpin to grnval
    softPwmWrite (BLUpin, bluval);  // Set the BLUpin to bluval
}

////////////////////////////////////////////////////////////////////////////////////////
//
// LED::setRed(): set the "red" attribute to the provided value
//
void LED::setRed(int32_t value)
{
    red = value;
}

////////////////////////////////////////////////////////////////////////////////////////
//
// LED::setGreen(): set the "green" attribute to the provided value
//
void LED::setGreen(int32_t value)
{
    green = value;
}

////////////////////////////////////////////////////////////////////////////////////////
//
// LED::setblue(): set the "blue" attribute to the provided value
//
void LED::setBlue(int32_t value)
{
    blue = value;
}

////////////////////////////////////////////////////////////////////////////////////////
//
// LED::getRed(): return the value of the "red" attribute
//
int32_t LED::getRed()
{
    return red;
}

////////////////////////////////////////////////////////////////////////////////////////
//
// LED::getGreen(): return the value of the "green" attribute
//
int32_t LED::getGreen()
{
    return green;
}

////////////////////////////////////////////////////////////////////////////////////////
//
// LED::getBlue(): return the value of the "blue" attribute
//
int32_t LED::getBlue()
{
    return blue;
}
