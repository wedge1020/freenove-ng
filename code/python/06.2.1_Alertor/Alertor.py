#!/usr/bin/env python3
########################################################################################
# Filename    : Alertor.py
# Description : Make Alertor with buzzer and button
# Author      : www.freenove.com
# modification: 2019/12/27
########################################################################################

########################################################################################
##
## import `TonalBuzzer`, `Button`, and `Tone` functionality from `gpiozero` library
##
from gpiozero import TonalBuzzer,Button
from gpiozero.tones import Tone

########################################################################################
##
## import the `time` and `math` libs
##
import time
import math

########################################################################################
##
## instantiating the TonalBuzzer class on pin 17
##
buzzer = TonalBuzzer(17)

########################################################################################
##
## instantiating the Button class on pin 18
##
button = Button(18)

def loop():
    while True:
        
        ################################################################################
        ##
        ## if button is pressed
        ##
        if button.is_pressed:
        
            ############################################################################
            ##
            ## start playing a repeating tone
            ##
            alertor()
            
            ############################################################################
            ##
            ## display operational information
            ##
            print ('alertor turned on >>> ')
            
        else:
        
            ############################################################################
            ##
            ## stop playing a repeating tone
            ##
            stopAlertor()
            
            ############################################################################
            ##
            ## display operational information
            ##
            print ('alertor turned off <<<')
            
########################################################################################
##
## start playing a repeating tone
##            
def alertor():
    
    ####################################################################################
    ##
    ## play a tone using the buzzer
    ##
    buzzer.play(Tone(220.0))
    
    ####################################################################################
    ##
    ## strategic delay for user perception (.1 seconds)
    ##
    time.sleep(0.1)
        
def stopAlertor():

    ####################################################################################
    ##
    ## stop playing the buzzer tone
    ##
    buzzer.stop()
            
def destroy():
    
    ####################################################################################
    ##
    ## closes the connection to the buzzer pin
    ##
    buzzer.close()                  

########################################################################################
##
## start of program
##
if __name__ == '__main__':

    ####################################################################################
    ##
    ## display operational information
    ##
    print ('Program is starting...')
    
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
