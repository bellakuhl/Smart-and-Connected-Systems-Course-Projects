# Range Finder
----------------

This repo contains the code for using a Sharp GP2Y0A02YK0F
IR sensor with an ESP32.

## Code
--------

The main program is range_finder.c. Once the ESP32 is connected and setup, run the following to build and flash the program:

```
idf.py build
idf.py flash
```

## Wiring
----------

GPIO34 ---------> Signal Pin on Sensor

USB    ---------> VCC on Sensor

GND    ---------> GND

**Note** a 10uF capacitor should be connected across the USB pin and GND to reduce noise.
