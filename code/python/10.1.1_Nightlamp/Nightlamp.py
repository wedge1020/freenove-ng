#!/usr/bin/env python3
#############################################################################
# Filename    : Nightlamp.py
# Description : Control LED with Photoresistor
# Author      : www.freenove.com
# modification: 2023/05/11
########################################################################
# Imports code libraries
from gpiozero import PWMLED
import time
# Importing necasary code from the ADCDevice file
from ADCDevice import *

ledPin = 17 # define ledPin
led = PWMLED(ledPin)
adc = ADCDevice() # Define an ADCDevice class object


# Checks if either pcf or ads is detected and if so assigns it to adc
# if neither is detected, an error message gets printed and 
# exits the program

def setup():
    global adc
    if(adc.detectI2C(0x48)): # Detect the pcf8591.
        adc = PCF8591()
    elif(adc.detectI2C(0x4b)): # Detect the ads7830
        adc = ADS7830()
    else:
        print("No correct I2C address found, \n"
        "Please use command 'i2cdetect -y 1' to check the I2C address! \n"
        "Exiting program. \n");
        exit(-1)

# Checks if this module is th main module and if so proceeds.
# Will than try to perform the loop function further down unless
# the keyboard interrupt shortcut is used which will end the program
if __name__ == '__main__':   # Program entrance
     print ('Program is starting... ')
     setup()
     try:
         loop()
     except KeyboardInterrupt:  # Press ctrl-c to end the program.
         destroy()
         print("Ending program")

# Adjusts the brightness of the light depending on the ADC value
def loop():
    while True:
        value = adc.analogRead(0)    # read the ADC value of channel 0
        led.value = value / 255.0    # Mapping to PWM duty cycle 
        voltage = value / 255.0 * 3.3
        print ('ADC Value : %d, Voltage : %.2f'%(value,voltage))
        time.sleep(0.01)

# Ends connection to led and device
def destroy():
    led.close()
    adc.close()
       
