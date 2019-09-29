#  Thermistor

Author: Isabella Kuhl, 2019-09-27

## Summary
In this skill I used a NTC mf52-103 (10K Ohm) thermistor to measure temperature. I did this by using the ADC on the ESP32 to record the voltage across the thermistor, as its resistance changes as a function of temperature. I used the 3.3v output from the board as I found this was less noisy than the USB 5v. A 10k resistor in series with the thermistor created a voltage divider that allowed me to measure the voltage drop across the thermistor. Combining the ADC to voltage equation and Ohm's law, I converted the input values to resistance and then used the [Steinhart-Hart](https://en.wikipedia.org/wiki/Steinhart%E2%80%93Hart_equation) to convert to Celsius.

## Sketches and Photos
Here is an image of the program running:
![skill16](https://github.com/BU-EC444/Kuhl-Isabella/blob/master/skills/cluster-2-sensor/16-thermistor/images/skill16.jpg)

## Modules, Tools, Source Used in Solution

* I referenced wikipedia for the [Steinhart-Hart](https://en.wikipedia.org/wiki/Steinhart%E2%80%93Hart_equation) equation.
* I referenced Espressif's [ADC guide](https://docs.espressif.com/projects/esp-idf/en/latest/api-reference/peripherals/adc.html#api-reference) for the ADC equation.
* I refernced the [thermistor's](https://www.eaa.net.au/PDF/Hitech/MF52type.pdf) datasheet to find the B value.
