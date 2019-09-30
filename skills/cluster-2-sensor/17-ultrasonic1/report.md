#  Ultrasonic 1

Author: Isabella Kuhl, 2019-09-29

## Summary
In this skill I interfaced with an Ultrasonic sensor and displayed the measured distance on the console. I did this using the ADC pin to receive the voltage from the sensor, then multiplied by 5 to get the distance in mm. Through testing, the minimum distance I could measure with this method is around 30mm and the error is ± 5cm.

## Sketches and Photos
Here is an image of the console while the program is running:

![skill 17](https://github.com/BU-EC444/Kuhl-Isabella/blob/master/skills/cluster-2-sensor/17-ultrasonic1/images/skill17.PNG)

## Modules, Tools, Source Used in Solution
* I referenced the [ultrasonic datasheet](https://www.maxbotix.com/documents/HRLV-MaxSonar-EZ_Datasheet.pdf) to find the range and formula for converting to mm.
* I adapted [Espressif's ADC code](https://github.com/espressif/esp-idf/blob/39f090a4f1dee4e325f8109d880bf3627034d839/examples/peripherals/adc/main/adc1_example_main.c) to use the ADC pin for this project.
