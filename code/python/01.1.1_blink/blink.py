#!/usr/bin/env python3
##
## Filename:    blink.py
## Description: basic usage of GPIO. Let LED blink.
##
########################################################################################

########################################################################################
##
## import `LED` functionality from `gpiozero` library, and `sleep` from `time` lib
##
from gpiozero import LED
from time import sleep

########################################################################################
##
## LEDpin is our LED instance connected to GPIO BCM pin (pin 17)
##
## The following addressing modes are available to use (these are all equivalent):
##
##    LEDpin = LED(17)           # BCM
##    LEDpin = LED("GPIO17")     # BCM
##    LEDpin = LED("BCM17")      # BCM
##    LEDpin = LED("BOARD11")    # BOARD
##    LEDpin = LED("WPI0")       # WiringPi
##    LEDpin = LED("J8:11")      # BOARD
##
LEDpin = LED(17)

def loop():
    while True:

        ################################################################################
        ##
        ## turn on the LED
        ##
        LEDpin.on()

        ################################################################################
        ##
        ## update information displayed to terminal
        ##
        print ("LED is: ON")

        ################################################################################
        ##
        ## strategic delay for user perception (1 second)
        ##
        sleep (1)

        ################################################################################
        ##
        ## turn off the LED
        ##
        LEDpin.off()

        ################################################################################
        ##
        ## update information displayed to terminal
        ##
        print ("LED is: OFF")  # print message on terminal

        ################################################################################
        ##
        ## strategic delay for user perception (1 second)
        ##
        sleep (1)    # wait 1 second

########################################################################################
##
## start of program
##
if __name__ == '__main__':

    ####################################################################################
    ##
    ## display operational information
    ##
    print ("Program is starting (CTRL-c to interrupt) ...")
    print (f"LEDpin is connected to pin: {LEDpin}\n")

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
    except KeyboardInterrupt:
        print ("ending program")
