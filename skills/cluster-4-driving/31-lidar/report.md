#  Lidar

Author: Laura Reeve, 11/03/19

## Summary

For this skill, we brought up the LidarLite (v1) using i2c. We have a function that reads in the distance every second using the following process: first, we write 0x04 to register 0x00, then we wait 20 ms, and then we read in the high (0x0f) and low (0x10) bytes and use these to get the distance. We reused the code that we used for the accelerometer to read and write to registers. 

## Sketches and Photos

<center>
    <img src="./images/lidar.jpg" width="80%">
<center>

Link to video: https://drive.google.com/open?id=1lnW5PRsM584g0Dd2f9kG71hcJk3DmZ8Z

## Modules, Tools, Source Used in Solution

Spec sheet: https://static.garmin.com/pumac/LIDAR_Lite_v3_Operation_Manual_and_Technical_Specifications.pdf

## Supporting Artifacts


-----

## Reminders
- Repo is private
