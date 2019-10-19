/* Isabella Kuhl
Adapted from Espressif's GPIO Example
This program turns the onboard LED on when the vibration switch is tapped. There is a 1 second buffer
between taps
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/gpio.h"

#define TILT_SWITCH_GPIO     4   // GPIO4 (A5) vibration switch
#define LED 13                   // onboard LED

static int flag = 0;            // interrupt flag
int state = 0;                  // state of LED


static void IRAM_ATTR gpio_isr_handler(void* arg)
{
      flag = 1;
}

static void tilt_switch_task(void* arg)
{
  while(1)
  {
    vTaskDelay(1000 / portTICK_RATE_MS);    // delay between taps
    if (flag == 1){
      state ^= 1;                           // toggle LED state
      flag = 0;                             // reset flag
    }
    gpio_set_level(LED, state);
  }
}

void app_main(void)
{
    gpio_pad_select_gpio(LED);
    gpio_set_direction(LED, GPIO_MODE_OUTPUT);
    gpio_set_level(LED, 0);                 // initialize LED to be OFF

    gpio_intr_enable(TILT_SWITCH_GPIO);     // enable interrupt
    gpio_set_intr_type(TILT_SWITCH_GPIO, GPIO_PIN_INTR_POSEDGE); // trigger interrupt on positive edge

    gpio_install_isr_service(ESP_INTR_FLAG_IRAM);
    gpio_isr_handler_add(TILT_SWITCH_GPIO, gpio_isr_handler, (void*) TILT_SWITCH_GPIO);

    xTaskCreate(tilt_switch_task, "tilt_switch_task", 2048, NULL, 10, NULL);

}
