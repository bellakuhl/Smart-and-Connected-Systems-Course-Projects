# Accelerometer
----------------

This repo contains the code for using an Adafruit ADXL343 accelerometer with an ESP32.

## Code
--------

The main program is accel.c. Once the ESP32 is connected and setup, run the following to build and flash the program:

```
idf.py build
idf.py flash
```

## Wiring
----------

SDA on ESP ---------> SDA on accelerometer

3V on ESP ---------> Vcc on accelerometer

SDL on ESP ---------> SDL on accelerometer

GND on ESP ---------> GND on accelerometer
