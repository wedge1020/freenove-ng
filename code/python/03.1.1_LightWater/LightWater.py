#!/usr/bin/env python3
########################################################################
# Filename    : LightWater.py
# Description : Use LED Bar Graph (10 LEDs)
# Author      : www.freenove.com
# Modification: 2023/05/11
########################################################################

from gpiozero import LED
from time import sleep

# LED pin numbers, using BCM numbering
ledPins = [17, 18, 27, 22, 23, 24, 25, 2, 3, 8]

# Create LED objects for each pin
leds = [LED(pin) for pin in ledPins]


def loop():
    while True:
                                # Move LED "on" from left to right
        for i in range(len(ledPins)):
            leds[i].off()
            sleep(0.1)
            leds[i].on()

                                # Move LED "on" from right to left
        for i in range(len(ledPins) - 1, -1, -1):
            leds[i].off()
            sleep(0.1)
            leds[i].on()


if __name__ == '__main__':     # Program entrance
    print("Program is starting...")
    try:
        loop()
    except KeyboardInterrupt:
        print("Ending program")
    finally:
                              # Clean up hardware resources
        for led in leds:
            led.close()
