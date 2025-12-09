#!/usr/bin/env python3
########################################################################################
# Filename    : ColorfulLED.py
# Description : Random color change ColorfulLED
# Author      : www.freenove.com
# modification: 2023/05/11
########################################################################################

########################################################################################
##
## import `RGBLED` functionality from `gpiozero` library
##
from gpiozero import RGBLED

########################################################################################
##
## import the `time` and `random` libs
##
import time
import random


########################################################################################
##
## instantiating the RGBLED class with specified pins and type for controlling the LED
##
## use first option for a common anode RGBLED and second for a common cathode RGBLED
##
## define the pins for R:11,G:12,B:13 
##
#led = RGBLED(red="J8:11", green="J8:12", blue="J8:13", active_high=False)
##
##define the pins for R:GPIO17,G:GPIO18,B:GPIO27 
##
led = RGBLED(red=17, green=18, blue=27, active_high=False)



########################################################################################
##
## change duty cycle for the three specified pins to r_val,g_val,b_val
##
def setColor(r_val,g_val,b_val):

    ####################################################################################
    ##
    ## change pwmRed duty cycle to r_val
    ##
    led.red=r_val/100
    
    ####################################################################################
    ##
    ## change pwmGreen duty cycle to g_value
    ##
    led.green = g_val/100
    
    ####################################################################################
    ##
    ## change pwmBlue duty cycle to b_val
    ##
    led.blue = b_val/100

def loop():
    while True:
    
        ################################################################################
        ##
        ## get three different random numbers in the range 0-100
        ##
        r=random.randint(0,100)  
        g=random.randint(0,100)
        b=random.randint(0,100)
        
        ################################################################################
        ##
        ## set the random numbers as the duty cycle values
        ##
        setColor(r,g,b)
        
        ################################################################################
        ##
        ## print the current RGB values
        ##
        print ('r=%d, g=%d, b=%d ' %(r ,g, b))
        
        
        ################################################################################
        ##
        ## strategic delay for user perception (1 second)
        ##
        time.sleep(1)
        
def destroy():

    ####################################################################################
    ##
    ## closes the connection to the LED pin
    ##
    led.close()

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
    ## normal operations: run the loop
    ##
    try:
        loop()
        
    ####################################################################################
    ##
    ## catch any keyboard interrupt characters to signal program exit
    ##
    except KeyboardInterrupt:  # Press ctrl-c to end the program.
        destroy()
        print("Ending program")
