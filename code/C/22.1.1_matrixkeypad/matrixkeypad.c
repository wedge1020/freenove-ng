//
// Filename:    matrixkeypad.c
// Description: Obtain the key code of 4x4 Matrix Keypad
//
////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////
//
// Pre-processor directives
//
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <wiringPi.h>
#include <keypad.h>

int32_t  main (void)
{
    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Declare and initialize variables
    //
    int8_t   key               = 0;
    uint8_t  ROWS              = 4; //four rows
    uint8_t  COLS              = 4; //four columns
    int8_t   keys[ROWS][COLS]  = {  //key code
      {'1','2','3','A'},
      {'4','5','6','B'},
      {'7','8','9','C'},
      {'*','0','#','D'}
    };
    uint8_t  rowPins[ROWS]     = { 1,  4, 5, 6 }; //define the row pins for the keypad
    uint8_t  colPins[COLS]     = { 12, 3, 2, 0 }; //define the column pins for the keypad

    //create Keypad object
    Keypad keypad  = Keypad (makeKeymap (keys), rowPins, colPins, ROWS, COLS);

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Bring wiringPi functionality online
    //
    if (wiringPiSetup ()      == -1)
    {
        fprintf (stderr, "[ERROR] Could not initialize wiringPi library!\n");
        exit (1);
    }

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Configure keypad
    //
    keypad.setDebounceTime (50);

    fprintf (stdout, "Program is starting (CTRL-c to interrupt) ...\n\n");

    while (1)
    {
        ////////////////////////////////////////////////////////////////////////////////
        //
        // Read from the keypad
        //
        key                    = keypad.getKey ();

        ////////////////////////////////////////////////////////////////////////////////
        //
        // If a key has been pressed, display which one was pressed (its "key code",
        // the character value)
        //
        if (key)
        {
            fprintf (stdout, "[KEYPAD] You pressed key: %c\n", key);
        }
    }

    return (0);
}
