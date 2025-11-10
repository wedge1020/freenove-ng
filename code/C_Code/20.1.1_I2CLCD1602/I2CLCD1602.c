//
// Filename:    I2CLCD1602.c
// Description: Use the LCD display data
// Components:  PCF8574, 1602 LCD
//
////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////
//
// Pre-processor directives
//
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <pcf8574.h>
#include <lcd.h>

#define  BASE    64         // BASE any number above 64

////////////////////////////////////////////////////////////////////////////////////////
//
// Define the output pins of the PCF8574, which are directly connected to the
// LCD1602 pin
//
////////////////////////////////////////////////////////////////////////////////////////

#define  RS      BASE+0
#define  RW      BASE+1
#define  EN      BASE+2
#define  LED     BASE+3
#define  D4      BASE+4
#define  D5      BASE+5
#define  D6      BASE+6
#define  D7      BASE+7

////////////////////////////////////////////////////////////////////////////////////////
//
// function prototypes
//
int32_t detectI2C           (int32_t);
void    printCPUTemperature (int32_t);
void    printDataTime       (int32_t);

int32_t main (void)
{
    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Declare and initialize local variables
    //
    int32_t  index         = 0;
    int32_t  lcdhd         = 0;    // LCD handle (passed to functions)
    int32_t  pcf8574_addr  = 0x27; // PCF8574T:0x27, PCF8574AT:0x3F

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Bring wiringPi functionality online
    //
    if (wiringPiSetup ()   == -1)
    {
        fprintf (stderr, "[ERROR] Could not initialize wiringPi library!\n");
        exit (1);
    }

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Attempt to detect where on the I2C bus the PCF8574 is located: 0x27
    //
    if (detectI2C (0x27))
    {
        pcf8574_addr       = 0x27;
    }

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Try #2: Attempt to detect where on the I2C bus the PCF8574 is located: 0x3F
    //
    else if (detectI2C (0x3F))
    {
        pcf8574_addr       = 0x3F;
    }

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Not found at either common address, kick back out an error
    //
    else
    {
        fprintf (stderr, "[ERROR] No valid I2C address found!\n");
        fprintf (stderr, "        Please use command 'i2cdetect -y 1' ");
        fprintf (stderr, "        to check the I2C address!\n");
        exit (2);
    }

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Initialize the PCF8574 at the found address
    //
    pcf8574Setup (BASE, pcf8574_addr);

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Set the PCF8574 ports to OUTPUT mode
    //
    for (index = 0; index < 8; index++)
    {
        pinMode ((BASE + index), OUTPUT);
    }

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Turn on the LCD backlight
    //
    digitalWrite (LED, HIGH);

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Allow writing to the LCD
    //
    digitalWrite (RW,  LOW);

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // initialize LCD and obtain handle to transact with the LCD
    //
    lcdhd                  = lcdInit (2, 16, 4, RS, EN, D4, D5, D6, D7, 0, 0, 0, 0);
    if (lcdhd             == -1)
    {
        fprintf (stderr, "[ERROR] LCD initialization failed!\n");
        exit (3);
    }

    fprintf (stdout, "Program is starting (CTRL-c to interrupt) ...\n");

    while (1)
    {
        ////////////////////////////////////////////////////////////////////////////////
        //
        // display the current CPU temperature to the LCD
        //
        printCPUTemperature (lcdhd);

        ////////////////////////////////////////////////////////////////////////////////
        //
        // display the current system time to the LCD
        //
        printDataTime (lcdhd);

        ////////////////////////////////////////////////////////////////////////////////
        //
        // strategic pause for user perception
        //
        delay (1000);
    }

    return (0);
}

int32_t detectI2C (int32_t  addr)
{
    int32_t  _fd                       = wiringPiI2CSetup (addr);
    int32_t  status                    = 0;

    if (_fd                           <  0)
    {
        fprintf (stderr, "[ERROR] could not setup i2c with address: 0x%x\n", addr);
        status                         = 0;
    }
    else
    {
        if (wiringPiI2CWrite (_fd, 0) <  0)
        {
            fprintf (stderr, "[i2c] Error: device not found (address: 0x%x)\n", addr);
            status                     = 0;
        }
        else
        {
            fprintf (stdout, "[i2c] Found device at address: 0x%x\n", addr);
            status                     = 1;
        }
    }

    return (status);
}

////////////////////////////////////////////////////////////////////////////////////////
//
// printCPUTemperature(): function used to print CPU temperature
//
void printCPUTemperature (int32_t  lcdhd)
{
    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Declare and initialize variables
    //
    char   str_temp[15];
    FILE  *fp        = NULL;
    float  CPU_temp  = 0.0;

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Open the file storing the CPU temperature on the system for reading
    //
    fp               = fopen ("/sys/class/thermal/thermal_zone0/temp", "r");
    if (fp          == NULL)
    {
        fprintf (stderr, "ERROR: Could not open file for reading\n");
        exit (4);
    }

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Read the temperature from the file
    //
    fgets (str_temp, 15, fp);

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Convert the temperature to Celcius
    //
    CPU_temp         = atof (str_temp) / 1000.0;

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Display the CPU temperature to the console
    //
    fprintf (stdout, "CPU temperature: %.2f\n", CPU_temp);

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Prepare the LCD screen for display: reset cursor position to 0, 0
    //
    lcdPosition (lcdhd, 0, 0);

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Display the CPU temperature on LCD
    //
    lcdPrintf (lcdhd, "CPU:%.2fC", CPU_temp);

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Close the open file
    //
    fclose (fp);
}

////////////////////////////////////////////////////////////////////////////////////////
//
// printDataTime(): function to display the system time
//
void printDataTime (int32_t  lcdhd)
{
    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Declare and initialize local variables
    //
    time_t     rawtime;
    struct tm *timeinfo  = NULL;

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Obtain the system time
    //
    time (&rawtime);

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Convert to local time
    //
    timeinfo             = localtime (&rawtime);

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Display time to console
    //
    fprintf (stdout, "%s\n", asctime (timeinfo));

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Prepare the LCD screen for display: reset cursor position to 0, 1 (second row)
    //
    lcdPosition (lcdhd, 0, 1);

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Display the system time on the LCD
    //
    lcdPrintf (lcdhd, "Time:%02d:%02d:%02d", timeinfo -> tm_hour,
                                             timeinfo -> tm_min,
                                             timeinfo -> tm_sec);
}

