#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/uart.h"

// Choosing some number 128 that is a multiple of 9
// to try to get whole frames.
#define RX_BUF_SIZE 20*9
const int uart_num = UART_NUM_1;

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

void app_main()
{
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
    while (1)
    {
        uart_flush(uart_num);
        int length = uart_read_bytes(uart_num, data, RX_BUF_SIZE, 20/portTICK_PERIOD_MS);
        uint32_t dist = 0;
        uint32_t strength = 0;
        average_readings(data, length, &dist, &strength);
        printf("Distance: %u (%u)\n", dist, strength);
    }
}

