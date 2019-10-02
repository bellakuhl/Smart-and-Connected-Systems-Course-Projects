/* Isabella Kuhl 09/26/19
Adapted from Espressif ADC1 Example
Program uses voltage divider with the USB voltage from the ESP32
to read in the voltage from ADC pin on the board. This
is then displayed on a alphanumeric display*/

#include <stdio.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "driver/adc.h"
#include "esp_adc_cal.h"
#include "esp_system.h"
#include "esp_spi_flash.h"
#include "driver/i2c.h"
#include "display_init.h"

#define DEFAULT_VREF    1100        //Use adc2_vref_to_gpio() to obtain a better estimate
#define NO_OF_SAMPLES   10          //Multisampling

static esp_adc_cal_characteristics_t *adc_chars;
static const adc_channel_t channel = ADC_CHANNEL_6;     //GPIO34 if ADC1, GPIO14 if ADC2
static const adc_atten_t atten = ADC_ATTEN_DB_11;
static const adc_unit_t unit = ADC_UNIT_1;

static void check_efuse(void)
{
    //Check TP is burned into eFuse
    if (esp_adc_cal_check_efuse(ESP_ADC_CAL_VAL_EFUSE_TP) == ESP_OK) {
        printf("eFuse Two Point: Supported\n");
    } else {
        printf("eFuse Two Point: NOT supported\n");
    }

    //Check Vref is burned into eFuse
    if (esp_adc_cal_check_efuse(ESP_ADC_CAL_VAL_EFUSE_VREF) == ESP_OK) {
        printf("eFuse Vref: Supported\n");
    } else {
        printf("eFuse Vref: NOT supported\n");
    }
}

static void print_char_val_type(esp_adc_cal_value_t val_type)
{
    if (val_type == ESP_ADC_CAL_VAL_EFUSE_TP) {
        printf("Characterized using Two Point Value\n");
    } else if (val_type == ESP_ADC_CAL_VAL_EFUSE_VREF) {
        printf("Characterized using eFuse Vref\n");
    } else {
        printf("Characterized using Default Vref\n");
    }
}

void app_main(void)
{
    // start the display
    alphadisplay_init();
    alphadisplay_start();

    //Check if Two Point or Vref are burned into eFuse
    check_efuse();
    char buffer[50];
    //Configure ADC
    if (unit == ADC_UNIT_1) {
        adc1_config_width(ADC_WIDTH_BIT_12);
        adc1_config_channel_atten(channel, atten);
    } else {
        adc2_config_channel_atten((adc2_channel_t)channel, atten);
    }

    //Characterize ADC
    adc_chars = calloc(1, sizeof(esp_adc_cal_characteristics_t));
    esp_adc_cal_value_t val_type = esp_adc_cal_characterize(unit, atten, ADC_WIDTH_BIT_12, DEFAULT_VREF, adc_chars);
    print_char_val_type(val_type);

    //Continuously sample ADC1
     while (1) {
         uint32_t adc_reading = 0;
         //Multisampling
         for (int i = 0; i < NO_OF_SAMPLES; i++) {
             if (unit == ADC_UNIT_1) {
                 adc_reading += adc1_get_raw((adc1_channel_t)channel);
             } else {
                 int raw;
                 adc2_get_raw((adc2_channel_t)channel, ADC_WIDTH_BIT_12, &raw);
                 adc_reading += raw;
             }
         }
         adc_reading /= NO_OF_SAMPLES;
         //Convert adc_reading to voltage in mV
         uint32_t voltage = esp_adc_cal_raw_to_voltage(adc_reading, adc_chars);

         sprintf(buffer, "%d", voltage);
         for (int e = 0; e < 4; e++) {
           alphadisplay_write_ascii(e, buffer[e]);
         }

         printf("Raw: %d\tVoltage: %dmV\n", adc_reading, voltage);
         vTaskDelay(pdMS_TO_TICKS(1000));
     }
 }
