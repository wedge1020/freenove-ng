#!/usr/bin/env python3
# Doorbell.py — simple buzzer doorbell using a button
# Cleansed and updated for EOCE Fall 2025

from gpiozero import Buzzer, Button
import time

# Hardware setup (BCM numbering)
buzzer = Buzzer(17)    # buzzer connected to GPIO17
button = Button(18)    # button connected to GPIO18

def onButtonPressed():
    """Callback: turn buzzer on when button is pressed."""
    buzzer.on()
    print("Button is pressed, buzzer turned on >>>")

def onButtonReleased():
    """Callback: turn buzzer off when button is released."""
    buzzer.off()
    print("Button is released, buzzer turned off <<<")

def loop():
    """Attach button callbacks and wait forever."""
    button.when_pressed = onButtonPressed
    button.when_released = onButtonReleased

    while True:
        time.sleep(1)

def destroy():
    """Release hardware resources before exiting."""
    buzzer.close()
    button.close()

if __name__ == '__main__':
    print("Program is starting...")
    try:
        loop()
    except KeyboardInterrupt:
        destroy()
        print("Ending program")
