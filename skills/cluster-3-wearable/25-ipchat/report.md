#  IP Chat

Author: Isabella Kuhl, 2019-10-23

## Summary

In this skill I used my PC as a client and the ESP32 as a server to send and receive messages. I did this using UDP protocol and adapting Espressif's UDP example to work with the PC and ESP IP addresses. I used Netcat running on Ubuntu to send and receive UDP packets from my PC.

## Sketches and Photos

Below is a screenshot of the console output after sending "Hello from PC":

![console output](https://github.com/BU-EC444/Kuhl-Isabella/blob/master/skills/cluster-3-wearable/25-ipchat/images/console.PNG)

## Modules, Tools, Source Used in Solution

* I referenced Espressif's [socket example](https://github.com/espressif/esp-idf/tree/master/examples/protocols/sockets) for setting up a UDP server.

* I used [Netcat](http://netcat.sourceforge.net/) to send and receive UDP packets from my PC.
-----

## Reminders
- Repo is private
