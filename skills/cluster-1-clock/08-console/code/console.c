// Isabella Kuhl 9/19/19

#include <stdio.h>
#include <string.h>
#include "driver/uart.h"
#include "esp_vfs_dev.h"

#define LED 13

void app_main()
{
    /* Install UART driver for interrupt-driven reads and writes */
    ESP_ERROR_CHECK( uart_driver_install(UART_NUM_0,
      256, 0, 0, NULL, 0) );

    /* Tell VFS to use UART driver */
    esp_vfs_dev_uart_use_driver(UART_NUM_0);

    gpio_pad_select_gpio(LED);
    gpio_set_direction(LED, GPIO_MODE_OUTPUT);

    int num = 0;
    char modes[3] =  {'t','e','d'};
    int i = 0;
    char cmd = 't';
    bool ON = true;
    while(1) {

      // gets()
      char buf[5];
      gets(buf);
      if (buf[0] == 's') {
        i += 1;
        if (i > 2) {
          i = 0;
        }
        cmd = modes[i];
      }
      //while (buf[0] != 's') {
        if (cmd == 't') {
          printf("toggle mode\n");
          printf("Read: %c\n", buf[0]);
          if (ON == true) {
            gpio_set_level(LED, 0);
            ON = false;
          } else {
            gpio_set_level(LED, 1);
            ON = true;
          }
        }
        else if (cmd == 'e') {
          printf("Echo: %s\n", buf);
        }
        else {
          printf("Enter an integer: \n");
          scanf("%d", &num);
          printf("Hex: %X\n", num);
        }
    }

      vTaskDelay(50 / portTICK_RATE_MS);
}
