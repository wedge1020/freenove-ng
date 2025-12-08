#!/usr/bin/env python3
##
## Filename:    tablelamp.py
## Description: DIY MINI table lamp
##
########################################################################################

from gpiozero import LED, Button
import time

led = LED(17)                  # define LED pin according to BCM numbering
button = Button(18)            # define Button pin according to BCM numbering

def onButtonPressed():         # When button is pressed, this will be executed
    led.toggle()
    if led.is_lit:
        print("button pressed: lamp turned on >>>")
    else:
        print("button pressed: lamp turned off <<<")

def loop():
    button.when_pressed = onButtonPressed # Button detect
    while True:
        time.sleep(1)
def destroy():
    led.close()
    button.close()
    print("GPIO resourses cleaned up.")

if __name__ == '__main__':     # Program entrance
    print ('Program is starting...')
    try:
        loop()
    except KeyboardInterrupt:  # Press ctrl-c to end the program.
        destroy()
        print("Ending program")
