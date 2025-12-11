//
// Filename:    alertor.cc
// Description: Make Alertor with BUZZER and BUTTON
// Components:  BUTTON, BUZZER
//
////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////
//
// Pre-processor directives: include header files for wiringPi and math libraries
//
#include <cmath>
#include <softTone.h>
#include <cstdint>
#include <cstdlib>
#include <wiringPi.h>
#include <iostream>

////////////////////////////////////////////////////////////////////////////////////////
//
// Class for storing alertor data
//
class alertor
{
    public:
    
    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Constructors
    //
    alertor();
    alertor(int32_t BUTpin, int32_t BUZpin);
    
    ////////////////////////////////////////////////////////////////////////////////////////
    //
    // Function prototypes for buzzer operation
    //
    void setupAlertor();
    void startAlertor(int32_t);
    void stopAlertor(int32_t);
    void runAlertor();
    
    private:
    
    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Declare variables for easier reference to our utilized wiringPi GPIOs
    //
    int32_t  BUTTONpin;     // declare the BUTTONpin
    int32_t  BUZZERpin;     // declare the BUZZERpin
};



int32_t  main (void)
{
    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Bring wiringPi functionality online
    //
    if (wiringPiSetup ()            == -1)
    {
        std::cout << "[ERROR] Could not initialize wiringPi library!\n";
        exit (1);
    }
    
    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Instantiate the alertor class
    //
    alertor newAlertor;
    
    newAlertor.setupAlertor();

    std::cout << "Program is starting (CTRL-c to interrupt) ...\n";
    std::cout << "[ALERTOR] turned OFF";

    while (1)
    {
        newAlertor.runAlertor();
    }

    return (0);
}

////////////////////////////////////////////////////////////////////////////////////
//
// Set pin modes for involved wiringPi GPIO pins, and configure button and buzzer
//
void alertor::setupAlertor()
{
    pinMode (BUTTONpin, INPUT);
    pinMode (BUZZERpin, OUTPUT);
    softToneCreate (BUZZERpin);           // set BUZZERpin for tone generation
    pullUpDnControl (BUTTONpin, PUD_UP);  // pull up to HIGH level
}

////////////////////////////////////////////////////////////////////////////////////////
//
// Generate an alert from the buzzer on indicated pin
//
void alertor::startAlertor (int32_t  pin)
{
    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Declare and initialize variables
    //
    int32_t  x        = 0;
    double   sinVal   = 0.0;
    double   toneVal  = 0.0;
    
    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Calculate and generate tone, utilizing the sine function
    //
    for (x = 0; x < 360; x++)
    {
        sinVal        = sin (x * (M_PI / 180)); // Calculate the sine value
        toneVal       = 2000 + sinVal * 500;    // Add frequency, weighted sine value
        softToneWrite (pin, toneVal);           // output corresponding PWM
        delay (1);
    }
}

////////////////////////////////////////////////////////////////////////////////////////
//
// alertor::alertor(): the parameterless constructor, initialize the member attributes
// to default values
//
alertor::alertor()
{
    BUTTONpin = 1;    // define the BUTTONpin
    BUZZERpin = 0;    // define the BUZZERpin
}

////////////////////////////////////////////////////////////////////////////////////////
//
// alertor::alertor(BUTpin, BUZpin): the parameterized constructor, initialize the member attributes to
// provided values
//
alertor::alertor(int32_t BUTpin, int32_t BUZpin)
{
    BUTTONpin = BUTpin;
    BUZZERpin = BUZpin;
}

////////////////////////////////////////////////////////////////////////////////////////
//
// Quiet the buzzer on indicated wiringPi GPIO pin
//
void alertor::stopAlertor (int32_t  pin)
{
    softToneWrite (pin, 0);
}

void alertor::runAlertor()
{
    ////////////////////////////////////////////////////////////////////////////////
    //
    // Button is pressed, generate alert using buzzer
    //
    if (digitalRead (BUTTONpin) == LOW)
    {
        startAlertor (BUZZERpin);
        std::cout << "\b\b\bON ";
    }

    ////////////////////////////////////////////////////////////////////////////////
    //
    // Button is released, quiet the buzzer
    //
    else
    {
        stopAlertor (BUZZERpin);
        std::cout << "\b\b\bOFF";
    }
}
