//
// Filename:    doorbell.cc
// Description: Make doorbell with buzzer and button.
// Components:  BUZZER, BUTTON
//
////////////////////////////////////////////////////////////////////////////////////////

// Preprocessor directives: include wiringPi, define symbols
#include <iostream>
#include <cstdint>
#include <wiringPi.h>

#define  BUTTONpin 1    // define the BUTTONpin
#define  BUZZERpin 0    // define the BUZZERpin

int32_t  main (void)
{
    // Bring wiringPi functionality online
    if (wiringPiSetup () == -1)
    {
        std::cout << "[ERROR] Could not initialize wiringPi library!" << std::endl;
        exit (1);
    }

    // Set pin modes for involved wiringPi GPIO pins, and configure button
    pinMode (BUTTONpin, INPUT);
    pinMode (BUZZERpin, OUTPUT);
    pullUpDnControl (BUTTONpin, PUD_UP);  // pull up to HIGH level

	// Print out program starting text
    std::cout << "Program is starting (CTRL-c to interrupt) ..." << std::endl;
    std::cout << "[BUZZER] turned OFF" << std::endl;

	// Main loop
    while (1)
    {
        // Button is pressed, turn on buzzer
        if (digitalRead (BUTTONpin) == LOW)
        {
            digitalWrite (BUZZERpin, HIGH);
            //fprintf (stdout, "\b\b\bON ");
        }

        // Button is released, turn off buzzer
        else
        {
            digitalWrite (BUZZERpin, LOW);
            //fprintf (stdout, "\b\b\bOFF");
        }
    }

    return (0);
}
