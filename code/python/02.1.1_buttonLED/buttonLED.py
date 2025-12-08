#!/usr/bin/env python3
##
## Filename:    buttonLED.py
## Description: Control LED with button.
##
########################################################################################

from gpiozero import LED, Button

led = LED(17)                      # define LED pin according to BCM numbering
button = Button(18)                # define Button pin according to BCM numbering

def loop():
    while True:
        if button.is_pressed:      # if button is pressed
            led.on()               # turn on LED
            print("Button is pressed, led turned on >>>")  # info to terminal
        else:                      # if button is released
            led.off()              # turn off LED
            print("Button is released, led turned off <<<")

if __name__ == '__main__':         # Program entrance
    print("Program is starting...")
    try:
        loop()
    except KeyboardInterrupt:      # Press Ctrl-C to stop program
        print("Ending program")
