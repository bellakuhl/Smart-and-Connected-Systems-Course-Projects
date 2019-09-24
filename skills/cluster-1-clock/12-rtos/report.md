#  RTOS

Author: Isabella Kuhl, 2019-09-20

## Summary
In this skill I used the TaskCreate on the ESP32 to create three tasks; the first one counted in binary, the second detects a button push, and the third displays the direction the binary counter is counting. By using TaskCreate the program can detect when the button has been pressed and, depending on the direction it was already counting in, it switches to either counting up or counting down.

## Sketches and Photos


## Modules, Tools, Source Used in Solution
I used [espressif example](https://github.com/espressif/esp-idf/blob/master/examples/peripherals/uart/uart_async_rxtxtasks/main/uart_async_rxtxtasks_main.c) code as a base for my program. I also used FreeRTOS's [tutorial](https://www.freertos.org/tutorial/) as a reference.
