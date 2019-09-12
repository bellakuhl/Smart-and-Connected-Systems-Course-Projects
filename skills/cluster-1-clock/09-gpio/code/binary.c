// Isabella Kuhl 9/12/19 blink-type program to count up, and wrap, in binary on the set of 4 LEDs

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "sdkconfig.h"

#define BLUE 13
#define YELLOW 12
#define RED 27
#define GREEN 33

void app_main()
{
    gpio_pad_select_gpio(BLUE);
    gpio_pad_select_gpio(YELLOW);
    gpio_pad_select_gpio(RED);
    gpio_pad_select_gpio(GREEN);
    /* Set the GPIO as a push/pull output */
    gpio_set_direction(BLUE, GPIO_MODE_OUTPUT);
    gpio_set_direction(YELLOW, GPIO_MODE_OUTPUT);
    gpio_set_direction(RED, GPIO_MODE_OUTPUT);
    gpio_set_direction(GREEN, GPIO_MODE_OUTPUT);

    int zero[] = {0,0,0,0};
    int one[] = {0,0,0,1};
    int two[] = {0,0,1,0};
    int three[] = {0,0,1,1};
    int four[] = {0,1,0,0};
    int five[] = {0,1,0,1};
    int six[] = {0,1,1,0};
    int seven[] = {0,1,1,1};
    int eight[] = {1,0,0,0};
    int nine[] = {1,0,0,1};
    int ten[] = {1,0,1,0};
    int eleven[] = {1,0,1,1};
    int twelve[] = {1,1,0,0};
    int thirteen[] = {1,1,0,1};
    int fourteen[] = {1,1,1,0};
    int fifteen[] = {1,1,1,1};

    int *nums[] = {zero, one, two, three, four, five, six, seven, eight, nine, ten, eleven, twelve, thirteen, fourteen, fifteen};
    while(1) {
      for (int i = 0; i <= 15; i++) {
          int *num = nums[i];
          gpio_set_level(BLUE, num[0]);
          gpio_set_level(YELLOW, num[1]);
          gpio_set_level(RED, num[2]);
          gpio_set_level(GREEN, num[3]);
          vTaskDelay(100);
        }
      }
    }
