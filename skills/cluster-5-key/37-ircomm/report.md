#  IR TX/RX

Author: Isabella Kuhl, 2019-11-20

## Summary

In this skill I implemented a program that both transmits a message corresponding to an LED to be turned on, when a button is pressed. The ESP is constantly receiving and when it receives a message, it lights up the corresponding LED. This was all done using UART on the ESP32. The finer details of the skill are I used the RMT on the ESP to transmit a 38kHz signal that is the carrier signal. This and the signal from the IR LED are ANDed by an H bridge which is then decoded by the IR receiver and sent to the UART. The H bridge also supplies the IR receiver with current since it requires more current than can be supplied by the ESP.

## Sketches and Photos

[Here]() is a link to a video demonstrating this skill.

This is an image of the circuit set up:
![TX RX](https://github.com/BU-EC444/Kuhl-Isabella/blob/master/skills/cluster-5-key/37-ircomm/images/ir-election_bb.png)

## Modules, Tools, Source Used in Solution

* I referenced Espressif's UART [example code](https://github.com/espressif/esp-idf/blob/master/examples/peripherals/uart/uart_echo/main/uart_echo_example_main.c)

-----

## Reminders
- Repo is private
