#!/usr/bin/env python3
########################################################################
# Filename    : ADC.py
# Description : Use ADC module to read the voltage value of potentiometer.
# Author      : www.freenove.com
# modification: 2023/05/11
########################################################################
# The first two import from code libraries while the third imports
# From the ADCDevice file that is also made
from gpiozero import PWMLED
import time
from ADCDevice import *

led = PWMLED(17,frequency=1000)      # define LED pin according to BCM Numbering
adc = ADCDevice() # Define an ADCDevice class object


# Detects which code is output and assigns it to adc
# If no code is found prints an error message and ends program
def setup():
    global adc
    if(adc.detectI2C(0x48)): # Detect the pcf8591.
        adc = PCF8591()
    elif(adc.detectI2C(0x4b)): # Detect the ads7830
        adc = ADS7830()
    else:
        print("No correct I2C address found, \n"
        "Please use command 'i2cdetect -y 1' to check the I2C address! \n"
        "Program Exit. \n");
        exit(-1)


# checks if loop is true and if so assigns the different values       
def loop():
    while True:
        value = adc.analogRead(0)      # read the ADC value of channel 0
        led.value = value / 255.0      # Mapping to PWM duty cycle       
        voltage = value / 255.0 * 3.3  # calculate the voltage value
        print ('ADC Value : %d, Voltage : %.2f'%(value,voltage))
        time.sleep(0.03)

# Function to stop/end the led and adc class
def destroy():
    led.close()
    adc.close()

# Detects if main is current module and if so will attempt the setup and loop
 # However if the KeyboardInterrupt will end the program
 if __name__ == '__main__':   # Program entrance
      print ('Program is starting ... ')
      try:
          setup()
          loop()
      except KeyboardInterrupt: # Press ctrl-c to end the program.
          destroy()
          print("Ending program")
    
