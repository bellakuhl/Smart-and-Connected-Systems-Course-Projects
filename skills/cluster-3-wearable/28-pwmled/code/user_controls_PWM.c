/* Isabella Kuhl 10/17/19
Adapted from brushed dc motor control example from Espressif
This program controls the brightness of an LED using PWM
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

float map(int x, int fromLOW, int fromHIGH, int toLOW, int toHIGH)  // map duty cycle to intensity values 0->9
{
  float value = toLOW + ((toHIGH - toLOW) / (fromHIGH - fromLOW)) * (x - fromLOW);
  return value;
}


static void set_LED_pwm(mcpwm_unit_t mcpwm_num, mcpwm_timer_t timer_num , float duty_cycle)
{
    mcpwm_set_signal_low(mcpwm_num, timer_num, MCPWM_OPR_B);
    mcpwm_set_duty(mcpwm_num, timer_num, MCPWM_OPR_A, duty_cycle);
    mcpwm_set_duty_type(mcpwm_num, timer_num, MCPWM_OPR_A, MCPWM_DUTY_MODE_0);
}

void app_main(void)
{
    printf("Enter an integer from 0 -> 9 to set LED intensity: \n");

    // mcpwm gpio initialization
    pwm_initialize();

    // initial mcpwm configuration
    mcpwm_config_t pwm_config;
    pwm_config.frequency = 1000;    //frequency = 500Hz,
    pwm_config.cmpr_a = 50;    //duty cycle of PWMxA = 50
    pwm_config.counter_mode = MCPWM_UP_COUNTER;
    pwm_config.duty_mode = MCPWM_DUTY_MODE_0;
    mcpwm_init(MCPWM_UNIT_0, MCPWM_TIMER_0, &pwm_config);    //Configure PWM0A with above settings

    while (1) {
        scanf("%d\n", &intensity);
        vTaskDelay(50 / portTICK_RATE_MS);
        if (intensity > 0) {
          float duty = map(intensity, 0, 9, 5, 95);  // map intensity to safe duty cycle range
          printf("duty set: %f \n", duty);
          set_LED_pwm(MCPWM_UNIT_0, MCPWM_TIMER_0, duty);
          intensity = 0;   // reset intensity
      }
    }
}
