#  Servos

Author: Isabella Kuhl, 2019-09-20

## Summary
In this skill I experimented with a SG90 servo. I adapted an example program from ESP to sweep the servo arm the full range - from 0 to 180 degrees. I did this by first experiementing with the frequency of the servos and then the minimum and maximum PWM values. I settled on 1000 to 2600 as this gave me the best result.

## Sketches and Photos
Here is an image of the servo running the program:
![skill 11](https://github.com/BU-EC444/Kuhl-Isabella/blob/master/skills/cluster-1-clock/11-servo/images/skill11.jpg)

## Modules, Tools, Source Used in Solution
[This](https://github.com/espressif/esp-idf/blob/master/examples/peripherals/mcpwm/mcpwm_servo_control/main/mcpwm_servo_control_example.c) is the example code I adapted from ESP's examples for my own use.

## Supporting Artifacts
Here is an image of the wiring for a SG90 servo (for future reference):
![SG90](https://github.com/BU-EC444/Kuhl-Isabella/blob/master/skills/cluster-1-clock/11-servo/images/Servo-Motor-Wires.png)
