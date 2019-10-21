# LED PWM
----------------

This repo contains the code for using PWM to control the brightness of an LED with an ESP32.

## Code
--------

There are two programs - intensity_cycle.c increases and decreases the intensity of the LED. The second program, user_controls_PWM.c allows user input to change the intensity from 0 to 9 (duty cycle 15 to 95).

Once the ESP32 is connected and setup, run the following to build and flash the program:

```
idf.py build
idf.py flash
```

## Wiring
----------

GPIO15 ---------> Positive Leg on LED

GND    ---------> Negative Leg on LED
