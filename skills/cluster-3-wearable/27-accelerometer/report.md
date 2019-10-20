#  Accelerometer

Author: Isabella Kuhl, 2019-10-19

## Summary
In this skill, my team and I wrote a program to read in and interpret values from the Adafruit ADXL343 accelerometer using I2C. We did this using I2C so that we are able to use multiple sensors on the bus with the same clock cycle.

## Sketches and Photos

Here is an image of the values read by the accelerometer:

[accel]()

## Modules, Tools, Source Used in Solution

* We referenced Emily Lam's [base code](https://github.com/BU-EC444/code-examples/tree/master/i2c-accel) for accelerometers.

* We referenced the [datasheet](https://cdn-learn.adafruit.com/assets/assets/000/070/556/original/adxl343.pdf?1549287964) for the accelerometer for connecting it and interpreting the values.

* We used DFRobot's [tutorial](https://wiki.dfrobot.com/How_to_Use_a_Three-Axis_Accelerometer_for_Tilt_Sensing) for the equations to translate the x, y, z values from the sensor into pitch, roll, and yaw.

-----

## Reminders
- Repo is private
