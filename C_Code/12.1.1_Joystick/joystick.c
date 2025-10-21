//
// Filename    : joystick.c
// Description : Read the Joystick
//               Uses simplified C port of ADCDevice library.
// Modification: 2025/10/21    
//
////////////////////////////////////////////////////////////////////////////////////////
        
#include <wiringPi.h>
#include <softPwm.h>
#include <stdio.h>
#include <stdlib.h>
#include <ADCDevice.h>

#define  Z_Pin  1     // define pin for Z-axis

////////////////////////////////////////////////////////////////////////////////////////
//  
// Declare Global ADCDevice variable
//  
ADCDevice *adc;
        
int main (void)
{       
    ////////////////////////////////////////////////////////////////////////////////////
    //  
    // Declare and initialize variables
    //  
    int  val_X     = 0;
    int  val_Y     = 0;
    int  val_Z     = 0;

    ////////////////////////////////////////////////////////////////////////////////////
    //  
    // Initialize the ADCDevice library
    //
    adc            = NULL;
    init_ADCDevice ();

    ////////////////////////////////////////////////////////////////////////////////////
    //  
    // Configure Z_Pin for input
    //
    pinMode (Z_Pin, INPUT);
    pullUpDnControl (Z_Pin, PUD_UP);    

    fprintf (stdout, "Program is starting (CTRL-c to interrupt) ...\n");

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Main loop: proceed indefinitely until interruption
    //
    while (1)
    {
        ////////////////////////////////////////////////////////////////////////////////
        //
        // Read joystick values
        //
        val_X      = adc -> analogRead (1); // read analog X-axis value
        val_Y      = adc -> analogRead (0); // read analog Y-axis value
        val_Z      = digitalRead (Z_Pin);   // read digital Z-axis value

        fprintf (stdout, "X: %3d, Y: %3d, Z: %d\n", val_X, val_Y, val_Z);
        delay (100);
    }

    return (0);
}
