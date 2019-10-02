#  Long Range IR Range Sensor

Author: Isabella Kuhl, 2019-10-02

## Summary
In this skill I use an IR sensor to detect an object's distance, similar to the ultrasonic skill. I used the ADC pin on the ESP to receive the voltage of the senor, which is then displayed on the console in meters. The sensor uses a 4.5 to 5.5v input so I used the USB port on the microcontroller to power the sensor. A capacitor across the USB pin and GND reduced fluctuations in voltage.

## Sketches and Photos


## Modules, Tools, Source Used in Solution

* I referenced the sensor's [datasheet](https://www.sparkfun.com/datasheets/Sensors/Infrared/gp2y0a02yk_e.pdf) to find the input voltage and recommended use.
* I adapted Espressif's [ADC code](https://github.com/espressif/esp-idf/blob/39f090a4f1dee4e325f8109d880bf3627034d839/examples/peripherals/adc/main/adc1_example_main.c) to be used with the IR sensor.
* I references Espressif's [ADC guide](https://docs.espressif.com/projects/esp-idf/en/latest/api-reference/peripherals/adc.html#api-reference) to find the attenuation value for the ADC pin.

-----

## Reminders
- Repo is private
