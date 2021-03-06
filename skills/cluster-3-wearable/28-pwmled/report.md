#  Use PWM to control power delivery to LEDs

Author: Isabella Kuhl, 2019-10-21

## Summary
In this skill I controlled the brightness of an LED using the PWM pins on the ESP32 and changing the duty cycle. I created two programs - one that takes user input, maps it to a safe duty cycle range for the LED, and sets the PWM using this duty cycle. The other program simply cycles through the LED brightness by counting up and down through the possible duty cycle values, incrementing by 5 every cycle.

## Sketches and Photos

Here is an image of the console output for the user inputted intensity:

![console](https://github.com/BU-EC444/Kuhl-Isabella/blob/master/skills/cluster-3-wearable/28-pwmled/images/user_control_console.PNG)

I recorded the execution of each program - [this](https://drive.google.com/open?id=1ZQX3c2jT8g6VZHE4jCSF82iuuqOUuJAH) is the link for user_controls_PWM.c and [this](https://drive.google.com/open?id=1WjDxi-cc-4Z69CB_e8u8wnhUpaz38PGo) is the link for intensity_cycle.c.

## Modules, Tools, Source Used in Solution

* I adapted Espressif's [motor control](https://github.com/espressif/esp-idf/blob/2e6398affaeeac2f7ce40457a881f2dda57ad11f/examples/peripherals/mcpwm/mcpwm_brushed_dc_control/main/mcpwm_brushed_dc_control_example.c) to use the PWM library.

* I referenced Espressif's [LED](https://docs.espressif.com/projects/esp-idf/en/latest/api-reference/peripherals/ledc.html) tutorial for API usage.

-----

## Reminders
- Repo is private
