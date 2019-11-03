/* Isabella Kuhl, Joseph Rossi, Laura Reeves
*  10/31/19
* This program implements PID control for speed control for the crawler
*/
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/timer.h"
#include <stdio.h>
#include "driver/uart.h"

#define DIVIDER 15000
#define TIMER_SCALE (TIMER_BASE_CLK/DIVIDER)
#define PID_TIMER (0.00002*TIMER_SCALE) // 0.1 seconds
#define HW_TIMER_GROUP TIMER_GROUP_0
#define HW_TIMER_IDX 0

#define RX_BUF_SIZE 20*9
const int uart_num = UART_NUM_1;

// PID constants
#define KP 0
#define KD 0
#define KI 0
#define SETPOINT 50

#define RED 12
#define GREEN 27
#define BLUE 33

// Flag for dt
int dt_complete = 0;

void average_readings(uint8_t *data, int len, uint32_t *distance, uint32_t *strength)
{
    int start_idx = -1;
    for (int i = 0; i < len-1; i++)
    {
        if (start_idx == -1 && data[i] == 0x59 && data[i+1] == 0x59)
        {
            start_idx = i;
            break;
        }
    }

    // If we didn't find a valid header or found one without
    // enough bytes to get a complete reading, skip.
    if (start_idx == -1 || (len - start_idx < 9)) {
        *distance = 0;
        *strength = 0;
        return;
    }

    size_t count = 0;
    uint32_t average_dist = 0;
    uint32_t average_str = 0;
    for (int i = start_idx; i < len - 8; i += 9)
    {
        // The checksum will overflow and wrap around.
        uint8_t checksum = 0;
        for (int j = 0; j < 8; j++) {
            checksum += data[i+j];
        }

        if (checksum != data[i + 8]) {
            printf("Warning - Checksum did not match. Expected %d, got %d\n",
                    data[i + 8], checksum);
            continue;
        }

        uint16_t dist = 0;
        dist |= data[i + 2] << 0;
        dist |= data[i + 3] << 4;
        average_dist += dist;

        uint16_t str = 0;
        str |= data[i + 4] << 0;
        str |= data[i + 5] << 4;
        average_str += str;

        count++;
    }

    average_dist /= count;
    average_str /= count;

    *distance = average_dist;
    *strength = average_str;
}

// Define timer interrupt handler
void IRAM_ATTR timer_isr()
{
    // Indicate timer has fired
    dt_complete = 1;
    // Clear interrupt
    TIMERG0.int_clr_timers.t0 = 1;
}

// Set up periodic timer for dt = 100ms
static void periodic_timer_init()
{
    // Basic parameters of the timer
    timer_config_t config = {
    .alarm_en = 1,
    .counter_en = 0,
    .intr_type = TIMER_INTR_LEVEL,
    .counter_dir = TIMER_COUNT_UP,
    .auto_reload = true,
    .divider = DIVIDER
  };

    // register timer interrupt
    timer_init(HW_TIMER_GROUP, HW_TIMER_IDX, &config);

    // Timer's counter will initially start from value below
    timer_set_counter_value(HW_TIMER_GROUP, HW_TIMER_IDX, 0);

    // Configure the alarm value and the interrupt on alarm.
    timer_set_alarm_value(HW_TIMER_GROUP, HW_TIMER_IDX, PID_TIMER);
    timer_enable_intr(HW_TIMER_GROUP, HW_TIMER_IDX);
    timer_isr_register(HW_TIMER_GROUP, HW_TIMER_IDX, timer_isr, NULL, ESP_INTR_FLAG_IRAM, NULL);

    // Start timer
    timer_start(HW_TIMER_GROUP, HW_TIMER_IDX);
}

// error for PID loop
int previous_error = 0;
int integral = 0;
int error = 0;
//float dt = 0.1;

int PID(int measured_value) {
  uint64_t timer_val;
  timer_get_counter_value(HW_TIMER_GROUP, HW_TIMER_IDX, &timer_val);
  double dt = ((double)timer_val / (double)TIMER_SCALE);
  error = SETPOINT - measured_value;
  //integral = integral + error * dt;
  //derivative = (error - previous_error) / dt;
  //output = KP * error + KI * integral + KD * derivative;
  previous_error = error;
  return error;
}


void app_main()
{
    periodic_timer_init();
    uart_config_t config = {
        .baud_rate = 115200,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .rx_flow_ctrl_thresh = 0
    };

    uart_param_config(uart_num, &config);
    uart_set_pin(uart_num, UART_PIN_NO_CHANGE, 16, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);
    uart_driver_install(uart_num, RX_BUF_SIZE, 0, 0, NULL, 0);
    uint8_t data[RX_BUF_SIZE];

    gpio_pad_select_gpio(BLUE);
    gpio_pad_select_gpio(RED);
    gpio_pad_select_gpio(GREEN);

    gpio_set_direction(BLUE, GPIO_MODE_OUTPUT);
    gpio_set_direction(RED, GPIO_MODE_OUTPUT);
    gpio_set_direction(GREEN, GPIO_MODE_OUTPUT);

    while (1)
    {

      uart_flush(uart_num);
      int length = uart_read_bytes(uart_num, data, RX_BUF_SIZE, 20/portTICK_PERIOD_MS);
      uint32_t dist = 0;
      uint32_t strength = 0;
      average_readings(data, length, &dist, &strength);
      printf("Distance: %u (%u)\n", dist, strength);
      if (dt_complete == 1)
      {
           int adjustment = PID(dist); // get error
           //printf("error: %d\n", adjustment);
           if (adjustment < 0)
           {
             gpio_set_level(RED, 1);
             gpio_set_level(BLUE, 0);
             gpio_set_level(GREEN, 0);
             vTaskDelay(10);
           }
           else if (adjustment > -5 && adjustment < 5)
           {
             gpio_set_level(RED, 0);
             gpio_set_level(BLUE, 0);
             gpio_set_level(GREEN, 1);
             vTaskDelay(10);
           }
           else
           {
             gpio_set_level(RED, 0);
             gpio_set_level(BLUE, 1);
             gpio_set_level(GREEN, 0);
             vTaskDelay(10);
           }
           dt_complete = 0; // reset flag
           // Re-enable alarm
           TIMERG0.hw_timer[TIMER_0].config.alarm_en = TIMER_ALARM_EN;
           vTaskDelay(10);
      }
    }
}
