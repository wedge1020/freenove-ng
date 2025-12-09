#!/usr/bin/env bash
##
## Filename:    Tablelamp.sh
## Description: DIY MINI table lamp
##
####################################################################################

####################################################################################
##
## Declare and initialize variables
##
LEDpin=0 ## wiringPi GPIO where LED is connected
BUTTONpin=1 ##wiringpi GPIO where the button is connected
LEDstate=0 ## the LEDs current state (HIGH or LOW)
HIGH=1 ## the wiringPi HIGH state
LOW=0 ## the wiringPi LOW state



####################################################################################
##
## configure the gpio pins
##
function setup_gpio() {
    
    ################################################################################
    ##
    ## setting the i/o mode 
    ##
    gpio mode $LEDpin out ## setting as output
    gpio mode $BUTTONpin in ## setting as input
    
    ################################################################################
    ##
    ## Enable pull-up resistor on button pin
    ##
    gpio mode $BUTTONpin up
    
    ################################################################################
    ##
    ## Initialize LED to off
    ##
    gpio write $LEDpin $LOW
}


####################################################################################
##
## toggles the LED when the button is pressed
##
function onButtonPressed() {
if [ $LEDstate -eq $LOW ]; then
    gpio write $LEDpin $HIGH
    LEDstate=$HIGH
    echo "LED turned on >>>"
else
    gpio write $LEDpin $LOW
    LEDstate=$LOW
    echo "LED turned off <<<"
fi
}


####################################################################################
##
## main program loop
##
function loop() {
    
    ################################################################################
    ##
    ## to store the current and last button state (high or low)
    ##
    local lastButtonState=$HIGH
    local currentButtonState
    
    while true; do
    
        ############################################################################
        ##
        ## reading the button state from gpio and storing it
        ##
        currentButtonState=$(gpio read $BUTTONpin)
    
    
        ############################################################################
        ##
        ## toggles the LED when the button is pressed
        ##
        if [ $lastButtonState -eq $HIGH ] && [ $currentButtonState -eq $LOW ]; then
        
            onButtonPressed
        
            ########################################################################
            ##
            ## debounce delay
            ##
            sleep 0.2
        fi
        
        lastButtonState=$currentButtonState

        ############################################################################
        ##
        ## poll every 0.05 seconds
        ##
        sleep 0.05
    done
}

####################################################################################
##
## sets the pins back to default configuration and prints exit message
##
function cleanup() {
    gpio write $LEDpin $LOW
    gpio mode $LEDpin in
    gpio mode $BUTTONpin down
    echo "Ending Program"
}


####################################################################################
##
## capture the interrupt signal (Ctrl+C) then run the cleanup function and exit
##
trap 'cleanup(); exit 0' SIGINT


####################################################################################
##
## Display operational information to STDOUT
##
echo "Program is starting (CTRL-c to interrupt) ..."

setup_gpio

loop
