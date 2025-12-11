#!/usr/bin/env python3
#############################################################################
# Filename    : Thermometer.py
# Description : DIY Thermometer
# Author      : www.freenove.com
# modification: December 10, 2025
########################################################################
#importing code libraries and everything from the ADCDEvice file
import time
import math
from ADCDevice import *

adc = ADCDevice() # Define an ADCDevice class object

# Detects which code is used and assins either PCF8591 or ADS7830 to ads
# Depending on which code is detrected.
# If anything else than those two codes are detected or none at all
# it prints an error and exits the program
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

# Creates an infiinite loop that while true will constantly calculate the values every
# 0.01s below and assign them, then it will print out the calculated information
# It does this by reading the ADC value, calculating the voltage and resistnace of
# the thermistor and using those values to calculate the kelvin temperature before
# Converting it to celsius.        
def loop():
    while True:
        value = adc.analogRead(0)        # read ADC value A0 pin
        voltage = value / 255.0 * 3.3        # calculate voltage
        Rt = 10 * voltage / (3.3 - voltage)    # calculate resistance value of thermistor
        tempK = 1/(1/(273.15 + 25) + math.log(Rt/10)/3950.0) # calculate temperature (Kelvin)
        tempC = tempK -273.15        # calculate temperature (Celsius)
        print ('ADC Value : %d, Voltage : %.2f, Temperature : %.2f'%(value,voltage,tempC))
        time.sleep(0.01)

# Garbage collection that will cleanly stop ads
def destroy():
    adc.close()
 
# Chgecks if the current module is the main module and not imported. If so it will
# print that the program is starting, go through the setup code above and try the loop
# checking for errors and will run that loop untill the keyboard interupt shortcut is
# used which will cleanly exit the program.   
if __name__ == '__main__':  # Program entrance
    print ('Program is starting ... ')
    setup()
    try:
        loop()
    except KeyboardInterrupt: # Press ctrl-c to end the program.
        destroy()
        print("Ending program")
