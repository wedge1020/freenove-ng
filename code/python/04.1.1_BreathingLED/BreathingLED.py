#!/usr/bin/env python3
########################################################################
# Filename    : BreathingLED.py
# Description : Breathing LED
# Author      : www.freenove.com
# modification: 2023/05/11
########################################################################

########################################################################################
##
## import `PWMLED` functionality from `gpiozero` library, and import the `time` lib
##
from gpiozero import PWMLED
import time

########################################################################################
##
## instantiating the PWMLED class for controlling the LED
##
led = PWMLED(18 ,initial_value=0 ,frequency=1000)

def loop():
    while True:
        
        ########################################################################################
        ##
        ## make the LED brighter
        ##
        for b in range(0, 101, 1):
            
            ########################################################################################
            ##
            ## set dc value as the duty cycle
            ##
            led.value = b / 100.0
            
            ########################################################################################
            ##
            ## strategic delay for user perception (.01 seconds)
            ##
            time.sleep(0.01)
        
        ########################################################################################
        ##
        ## strategic delay for user perception (1 second)
        ##
        time.sleep(1)
        
        ########################################################################################
        ##
        ## make the LED darker
        ##
        for b in range(100, -1, -1):
        
            ########################################################################################
            ##
            ## set dc value as the duty cycle
            ##
            led.value = b / 100.0
            
            ########################################################################################
            ##
            ## strategic delay for user perception (.01 seconds)
            ##
            time.sleep(0.01)
            
        ########################################################################################
        ##
        ## strategic delay for user perception (1 second)
        ##
        time.sleep(1)
        
        
def destroy():

    ########################################################################################
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
