/* Isabella Kuhl 10/21/19
Adapted from brushed dc motor control example from Espressif
This program cycles through the brightness of an LED
*/

#include <stdio.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_attr.h"
#include <string.h>
#include "driver/uart.h"
#include "esp_vfs_dev.h"

#include "driver/mcpwm.h"

#define LED_GPIO 15   //Set GPIO 15 as PWM0A

int intensity; // inputted intensity of LED

static void pwm_initialize(void)
{
    mcpwm_gpio_init(MCPWM_UNIT_0, MCPWM0A, LED_GPIO);
}


static void set_LED_pwm(mcpwm_unit_t mcpwm_num, mcpwm_timer_t timer_num , float duty_cycle)
{
    mcpwm_set_signal_low(mcpwm_num, timer_num, MCPWM_OPR_B);
    mcpwm_set_duty(mcpwm_num, timer_num, MCPWM_OPR_A, duty_cycle);
    mcpwm_set_duty_type(mcpwm_num, timer_num, MCPWM_OPR_A, MCPWM_DUTY_MODE_0);
}

void app_main(void)
{
    printf("Cycling through LED brightness!\n");

    // mcpwm gpio initialization
    pwm_initialize();

    // initial mcpwm configuration
    mcpwm_config_t pwm_config;
    pwm_config.frequency = 1000;    //frequency = 500Hz,
    pwm_config.cmpr_a = 5;    //duty cycle of PWMxA = 50
    pwm_config.counter_mode = MCPWM_UP_COUNTER;
    pwm_config.duty_mode = MCPWM_DUTY_MODE_0;
    mcpwm_init(MCPWM_UNIT_0, MCPWM_TIMER_0, &pwm_config);    //Configure PWM0A with above settings

    bool direction = 1;  // 0 is down, 1 is up

    while (1) {
        if (direction == 1)
        {
          for (int i = 0; i <= 95; i += 5)   // 95 is max duty cycle to prevent LED burnout
          {
            set_LED_pwm(MCPWM_UNIT_0, MCPWM_TIMER_0, i);
            vTaskDelay(250 / portTICK_RATE_MS);   // wait 250ms
          }
          direction = 0;  // change direction
        }
        else
        {
          for (int i = 95; i >= 0; i -= 5)
          {
            set_LED_pwm(MCPWM_UNIT_0, MCPWM_TIMER_0, i);
            vTaskDelay(250 / portTICK_RATE_MS);   // wait 250ms
          }
          direction = 0;  // change direction
        }
        vTaskDelay(50 / portTICK_RATE_MS);
    }
}
