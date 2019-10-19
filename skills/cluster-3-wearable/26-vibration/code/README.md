# Tilt Switch
----------------

This repo contains the code for using an Adafruit's Fast Vibration Sensor Switch with an ESP32.

## Code
--------

The main program is tilt.c. Once the ESP32 is connected and setup, run the following to build and flash the program:

```
idf.py build
idf.py flash
```

## Wiring
----------

GPIO4 ---------> Lead on Switch (either one)

![Diagram](https://github.com/BU-EC444/Kuhl-Isabella/blob/master/skills/cluster-3-wearable/26-vibration/images/switch-pullup.jpg)
