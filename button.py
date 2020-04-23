#!/usr/bin/env python3
#
# Licensed under MIT license. See full license in LICENSE file.
#
# Author: Jarett Rude

from gpiozero import LED, Button, DigitalOutputDevice
from time import sleep
from signal import pause
from subprocess import check_call
import uinput

# SHUTDOWN BUTTON
def shutdown():
    check_call(['sudo', 'poweroff'])
shutdown_btn = Button(21)

# DEFINE TIGGER BUTTON WITH LED
triggerLED = LED(18)
triggerButton = Button(4)

# DEFINE SIGNAL TO ARDUINO FOR LIGHTS
arduinoTrigger = DigitalOutputDevice(13,active_high=True,initial_value=False)
def send():
    arduinoTrigger.on()
    #print(arduinoTrigger.value)
    sleep(2)
    arduinoTrigger.off()

while True:
    triggerLED.on()
    if triggerButton.is_pressed:
        #print("pressed")
        with uinput.Device([uinput.KEY_ENTER]) as device:
            sleep(1)
            device.emit_combo([uinput.KEY_ENTER])
            send()
            sleep(8)
    if shutdown_btn.is_pressed:
        #print("shutdown")
        shutdown()

pause()