#!/usr/bin/env python3
########################################################################################
# Filename    : ADC.py
# Description : Use ADC module to read the voltage value of potentiometer.
# Author      : www.freenove.com
# modification: 2023/05/11
########################################################################################

########################################################################################
##
## import the `time` lib and import the ADCDevice module
##
import time
from ADCDevice import *

########################################################################################
##
## instantiating the ADCDevice class
##
adc = ADCDevice()

########################################################################################
##
## sets up the adc object
##
def setup():

    ####################################################################################
    ##
    ## using the global adc object
    ##
    global adc
    
    ####################################################################################
    ##
    ## detect the type of ADC then instantiate the detected device class
    ##
    if(adc.detectI2C(0x48)): # Detect the pcf8591.
        adc = PCF8591()
    elif(adc.detectI2C(0x4b)): # Detect the ads7830
        adc = ADS7830()
    
    ####################################################################################
    ##
    ## if no device is detected, display the message below and exit the program
    ##
    else:
        print("No correct I2C address found, \n"
        "Please use command 'i2cdetect -y 1' to check the I2C address! \n"
        "Program Exit. \n");
        exit(-1)
        
def loop():
    while True:
    
        ################################################################################
        ##
        ## read the ADC value of channel 0
        ##
        value = adc.analogRead(0)
        
        ################################################################################
        ##
        ## calculate the voltage value
        ##
        voltage = value / 255.0 * 3.3
        
        ################################################################################
        ##
        ## display the ADC value and voltage
        ##
        print ('ADC Value : %d, Voltage : %.2f'%(value,voltage))
        
        ################################################################################
        ##
        ## strategic delay for user perception (0.1 seconds)
        ##
        time.sleep(0.1)

def destroy():

    ####################################################################################
    ##
    ## close the connection to the ADC pin
    ##
    adc.close()
    
########################################################################################
##
## start of program
##
if __name__ == '__main__':

    ####################################################################################
    ##
    ## display operational information
    ##
    print ('Program is starting ... ')
    
    ####################################################################################
    ##
    ## normal operations: run the setup function and run the loop
    ##
    try:
        setup()
        loop()
        
    ####################################################################################
    ##
    ## catch any keyboard interrupt characters to signal program exit
    ##
    except KeyboardInterrupt: # Press ctrl-c to end the program.
        destroy()
        print("Ending program")
