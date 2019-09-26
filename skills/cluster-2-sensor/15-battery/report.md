#  Battery Monitor

Author: Isabella Kuhl, 2019-09-26

## Summary
In this skill I created a program that receives an input voltage into the ADC and displays it on an alphanumeric display. I use the 5v from the USB port on the ESP32 and use a voltage divider to get 2.5v to stay within the ADCs 0 - 3.3v range.

## Sketches and Photos
Here is an image of the program running:
![skill15](https://github.com/BU-EC444/Kuhl-Isabella/blob/master/skills/cluster-2-sensor/15-battery/images/skill13.jpg)

## Modules, Tools, Source Used in Solution
1. I used Espressif [ADC example](https://github.com/espressif/esp-idf/blob/39f090a4f1dee4e325f8109d880bf3627034d839/examples/peripherals/adc/main/adc1_example_main.c) code and adapted it to display the values.
2. I referenced Espressif's [ADC guide](https://docs.espressif.com/projects/esp-idf/en/latest/api-reference/peripherals/adc.html#api-reference) to change the attenuation value.
