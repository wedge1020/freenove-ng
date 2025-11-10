#!/usr/bin/env bash
##
## Filename:    blink.c
## Description: basic usage of GPIO. Let LED blink.
## Components:  LED
##
########################################################################################

########################################################################################
##
## Declare and initialize variables
##
LEDpin=0 ## wiringPi GPIO where LED is connected
HIGH=1   ## the wiringPi HIGH state
LOW=0    ## the wiringPi LOW state

########################################################################################
##
## configure the LED component for OUTPUT
##
gpio mode ${LEDpin} out

########################################################################################
##
## Display operational information to STDOUT
##
echo "Program is starting (CTRL-c to interrupt) ..."
echo "[LED] configured for OUTPUT mode using pin: ${LEDpin}"
echo

########################################################################################
##
## Display the default status (note the lack of newline at the end, so that with
## the strategic use of backspaces, we can update this line in place)
##
printf "LED: OFF"

while [ true ]; do

    ####################################################################################
    ##
    ## Turn LED on (set to HIGH state)
    ##
    gpio write ${LEDpin} ${HIGH}

    ####################################################################################
    ##
    ## update information display to report current LED state
    ##
    printf "\b\b\bON "

    ####################################################################################
    ##
    ## strategic delay for user perception (1 second)
    ##
    sleep 1

    ####################################################################################
    ##
    ## Turn LED off (set to LOW state)
    ##
    gpio write ${LEDpin} ${LOW}

    ####################################################################################
    ##
    ## update information display to report current LED state
    ##
    printf "\b\b\bOFF"

    ####################################################################################
    ##
    ## strategic delay for user perception (1 second)
    ##
    sleep 1
done

exit 0
