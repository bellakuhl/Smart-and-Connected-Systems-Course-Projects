#  Vibration switch (hardware interrupts)

Author: Isabella Kuhl, 2019-10-19

## Summary

In this skill I explored hardware interrupts to toggle the state of the ESP32's onboard LED. I used GPIO 4 and a pull-up resistor to trigger the interrupt whenever the switch is tapped. Because the switch can close and open rapidly when tapped I used a flag and a one second delay to only allow the state of the LED to be changed once a second. An issue I ran into when using the interrupt was that a vTaskDelay was needed in the while loop before checking the state of the flag and setting the LED state because the main loop was executing and triggering the watchdog.

## Sketches and Photos

I took a [video](https://drive.google.com/open?id=1XBZbHV4IFKMORpQ8uo67Iz2TnLU6GBxw) of the program executing to demonstrate this skill.

## Modules, Tools, Source Used in Solution

* I adapted Espressif's [GPIO hardware interrupt](https://github.com/espressif/esp-idf/blob/master/examples/peripherals/gpio/main/gpio_example_main.c) example.

* I referenced [course material](http://whizzer.bu.edu/briefs/design-patterns/dp-interrupts) for the design pattern of interrupts.


-----

## Reminders
- Repo is private
