#  Long Range IR Range Sensor

Author: Isabella Kuhl, 2019-10-02

## Summary
In this skill I use an IR sensor to detect an object's distance, similar to the ultrasonic skill. I used the ADC pin on the ESP to receive the voltage of the senor, which is then displayed on the console in meters. In order to convert the voltage to distance, I used Sharp's formula found in their [Arduino library](https://github.com/guillaume-rico/SharpIR/blob/master/SharpIR.cpp) The sensor uses a 4.5 to 5.5v input so I used the USB port on the microcontroller to power the sensor. A capacitor across the USB pin and GND reduced fluctuations in voltage.

## Sketches and Photos
Here is an image of the console output as I move my hand at varying distances in front of the sensor:

![console](https://github.com/BU-EC444/Kuhl-Isabella/blob/master/skills/cluster-2-sensor/18-rangefinder/images/skill18a.PNG)

Here is an image of the sensor wiring setup:

![wiring](https://github.com/BU-EC444/Kuhl-Isabella/blob/master/skills/cluster-2-sensor/18-rangefinder/images/skill18b.jpg)

## Modules, Tools, Source Used in Solution

* I referenced the sensor's [datasheet](https://www.sparkfun.com/datasheets/Sensors/Infrared/gp2y0a02yk_e.pdf) to find the input voltage and recommended use.
* I referenced Sharp's [Arduino library](https://github.com/guillaume-rico/SharpIR/blob/master/SharpIR.cpp) for the formula for converting between voltage and distance.
* I adapted Espressif's [ADC code](https://github.com/espressif/esp-idf/blob/39f090a4f1dee4e325f8109d880bf3627034d839/examples/peripherals/adc/main/adc1_example_main.c) to be used with the IR sensor.
* I references Espressif's [ADC guide](https://docs.espressif.com/projects/esp-idf/en/latest/api-reference/peripherals/adc.html#api-reference) to find the attenuation value for the ADC pin.

-----

## Reminders
- Repo is private
