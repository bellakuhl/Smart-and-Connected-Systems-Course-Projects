// Isabella Kuhl 09/23/19 Adpated from FreeRTOS example

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_spi_flash.h"
#include "sdkconfig.h"
#include "driver/gpio.h"
#include "driver/i2c.h"
#include "esp_vfs_dev.h"

#define SLAVE_ADDR                         0x70 // alphanumeric address
#define OSC                                0x21 // oscillator cmd
#define HT16K33_BLINK_DISPLAYON            0x01 // Display on cmd
#define HT16K33_BLINK_OFF                  0    // Blink off cmd
#define HT16K33_BLINK_CMD                  0x80 // Blink cmd
#define HT16K33_CMD_BRIGHTNESS             0xE0 // Brightness cmd

// Master I2C
#define I2C_EXAMPLE_MASTER_SCL_IO          22   // gpio number for i2c clk
#define I2C_EXAMPLE_MASTER_SDA_IO          23   // gpio number for i2c data
#define I2C_EXAMPLE_MASTER_NUM             I2C_NUM_0  // i2c port
#define I2C_EXAMPLE_MASTER_TX_BUF_DISABLE  0    // i2c master no buffer needed
#define I2C_EXAMPLE_MASTER_RX_BUF_DISABLE  0    // i2c master no buffer needed
#define I2C_EXAMPLE_MASTER_FREQ_HZ         100000     // i2c master clock freq
#define WRITE_BIT                          I2C_MASTER_WRITE // i2c master write
#define READ_BIT                           I2C_MASTER_READ  // i2c master read
#define ACK_CHECK_EN                       true // i2c master will check ack
#define ACK_CHECK_DIS                      false// i2c master will not check ack
#define ACK_VAL                            0x00 // i2c ack value
#define NACK_VAL                           0xFF // i2c nack value

#define BLUE 13
#define YELLOW 12
#define RED 27
#define GREEN 33
#define BUTTON 15

bool dir = true; // true -> counting UP
uint16_t displaybuffer[8]; // char buffer for alphanumeric display

// binary values
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
//array to hold binary values
int *nums[] = {zero, one, two, three, four, five, six,
  seven, eight, nine, ten, eleven, twelve, thirteen, fourteen, fifteen};

int ret; // used in alphanumeric display init

static void i2c_example_master_init(){
    // Debug
    printf("\n>> i2c Config\n");
    int err;

    // Port configuration
    int i2c_master_port = I2C_EXAMPLE_MASTER_NUM;

    /// Define I2C configurations
    i2c_config_t conf;
    conf.mode = I2C_MODE_MASTER;                              // Master mode
    conf.sda_io_num = I2C_EXAMPLE_MASTER_SDA_IO;              // Default SDA pin
    conf.sda_pullup_en = GPIO_PULLUP_ENABLE;                  // Internal pullup
    conf.scl_io_num = I2C_EXAMPLE_MASTER_SCL_IO;              // Default SCL pin
    conf.scl_pullup_en = GPIO_PULLUP_ENABLE;                  // Internal pullup
    conf.master.clk_speed = I2C_EXAMPLE_MASTER_FREQ_HZ;       // CLK frequency
    err = i2c_param_config(i2c_master_port, &conf);           // Configure
    if (err == ESP_OK) {printf("- parameters: ok\n");}

    // Install I2C driver
    err = i2c_driver_install(i2c_master_port, conf.mode,
                       I2C_EXAMPLE_MASTER_RX_BUF_DISABLE,
                       I2C_EXAMPLE_MASTER_TX_BUF_DISABLE, 0);
    // i2c_set_data_mode(i2c_master_port,I2C_DATA_MODE_LSB_FIRST,I2C_DATA_MODE_LSB_FIRST);
    if (err == ESP_OK) {printf("- initialized: yes\n\n");}

    // Dat in MSB mode
    i2c_set_data_mode(i2c_master_port, I2C_DATA_MODE_MSB_FIRST, I2C_DATA_MODE_MSB_FIRST);
}

// Utility  Functions //////////////////////////////////////////////////////////

// Utility function to test for I2C device address -- not used in deploy
int testConnection(uint8_t devAddr, int32_t timeout) {
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (devAddr << 1) | I2C_MASTER_WRITE, ACK_CHECK_EN);
    i2c_master_stop(cmd);
    int err = i2c_master_cmd_begin(I2C_EXAMPLE_MASTER_NUM, cmd, 1000 / portTICK_RATE_MS);
    i2c_cmd_link_delete(cmd);
    return err;
}

// Utility function to scan for i2c device
static void i2c_scanner() {
    int32_t scanTimeout = 1000;
    printf("\n>> I2C scanning ..."  "\n");
    uint8_t count = 0;
    for (uint8_t i = 1; i < 127; i++) {
        // printf("0x%X%s",i,"\n");
        if (testConnection(i, scanTimeout) == ESP_OK) {
            printf( "- Device found at address: 0x%X%s", i, "\n");
            count++;
        }
    }
    if (count == 0)
        printf("- No I2C devices found!" "\n");
    printf("\n");
}

////////////////////////////////////////////////////////////////////////////////

// Alphanumeric Functions //////////////////////////////////////////////////////

// Turn on oscillator for alpha display
int alpha_oscillator() {
  int ret;
  i2c_cmd_handle_t cmd = i2c_cmd_link_create();
  i2c_master_start(cmd);
  i2c_master_write_byte(cmd, ( SLAVE_ADDR << 1 ) | WRITE_BIT, ACK_CHECK_EN);
  i2c_master_write_byte(cmd, OSC, ACK_CHECK_EN);
  i2c_master_stop(cmd);
  ret = i2c_master_cmd_begin(I2C_EXAMPLE_MASTER_NUM, cmd, 1000 / portTICK_RATE_MS);
  i2c_cmd_link_delete(cmd);
  vTaskDelay(200 / portTICK_RATE_MS);
  return ret;
}

// Set blink rate to off
int no_blink() {
  int ret;
  i2c_cmd_handle_t cmd2 = i2c_cmd_link_create();
  i2c_master_start(cmd2);
  i2c_master_write_byte(cmd2, ( SLAVE_ADDR << 1 ) | WRITE_BIT, ACK_CHECK_EN);
  i2c_master_write_byte(cmd2, HT16K33_BLINK_CMD | HT16K33_BLINK_DISPLAYON | (HT16K33_BLINK_OFF << 1), ACK_CHECK_EN);
  i2c_master_stop(cmd2);
  ret = i2c_master_cmd_begin(I2C_EXAMPLE_MASTER_NUM, cmd2, 1000 / portTICK_RATE_MS);
  i2c_cmd_link_delete(cmd2);
  vTaskDelay(200 / portTICK_RATE_MS);
  return ret;
}

// Set Brightness
int set_brightness_max(uint8_t val) {
  int ret;
  i2c_cmd_handle_t cmd3 = i2c_cmd_link_create();
  i2c_master_start(cmd3);
  i2c_master_write_byte(cmd3, ( SLAVE_ADDR << 1 ) | WRITE_BIT, ACK_CHECK_EN);
  i2c_master_write_byte(cmd3, HT16K33_CMD_BRIGHTNESS | val, ACK_CHECK_EN);
  i2c_master_stop(cmd3);
  ret = i2c_master_cmd_begin(I2C_EXAMPLE_MASTER_NUM, cmd3, 1000 / portTICK_RATE_MS);
  i2c_cmd_link_delete(cmd3);
  vTaskDelay(200 / portTICK_RATE_MS);
  return ret;
}

void init() {

  // Debug
  printf(">> Test Alphanumeric Display: \n");

  // Set up routines
  // Turn on alpha oscillator
  ret = alpha_oscillator();
  if(ret == ESP_OK) {printf("- oscillator: ok \n");}
  // Set display blink off
  ret = no_blink();
  if(ret == ESP_OK) {printf("- blink: off \n");}
  ret = set_brightness_max(0xF);
  if(ret == ESP_OK) {printf("- brightness: max \n");}

  // init alphanumeric display
  i2c_example_master_init();
  i2c_scanner();
  // init LEDs and binary vectors
  gpio_pad_select_gpio(BLUE);
  gpio_pad_select_gpio(YELLOW);
  gpio_pad_select_gpio(RED);
  gpio_pad_select_gpio(GREEN);
  gpio_pad_select_gpio(BUTTON);

  gpio_set_direction(BLUE, GPIO_MODE_OUTPUT);
  gpio_set_direction(YELLOW, GPIO_MODE_OUTPUT);
  gpio_set_direction(RED, GPIO_MODE_OUTPUT);
  gpio_set_direction(GREEN, GPIO_MODE_OUTPUT);

  gpio_set_direction(BUTTON, GPIO_MODE_INPUT);
}

	static void binary(void *arg)         // task 1
	{
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

	static void button_press(void *arg)			// task 2
	{
		while(1){
			if (dir == true) {dir = false;}
      else {dir = true;}
		}
	}

  static void alpha(void *arg)			// task 3
  {
    while (1) {

			if (dir == true) {
					displaybuffer[0] = 0b0000000000111110;
          displaybuffer[1] = 0b0000000011110011;
          displaybuffer[2] = 0b0000000000000000;
          displaybuffer[3] = 0b0000000000000000;
        }
			else {
          displaybuffer[0] = 0b0001001000001111;
          displaybuffer[1] = 0b0000000000111111;
          displaybuffer[2] = 0b0010100000110110;
          displaybuffer[3] = 0b0010000100110110;
				}

			vTaskDelay(50 / portTICK_RATE_MS);
      // Send commands characters to display over I2C
      i2c_cmd_handle_t cmd4 = i2c_cmd_link_create();
      i2c_master_start(cmd4);
      i2c_master_write_byte(cmd4, ( SLAVE_ADDR << 1 ) | WRITE_BIT, ACK_CHECK_EN);
      i2c_master_write_byte(cmd4, (uint8_t)0x00, ACK_CHECK_EN);
      for (uint8_t i=0; i<8; i++) {
        i2c_master_write_byte(cmd4, displaybuffer[i] & 0xFF, ACK_CHECK_EN);
        i2c_master_write_byte(cmd4, displaybuffer[i] >> 8, ACK_CHECK_EN);
      }
      i2c_master_stop(cmd4);
      ret = i2c_master_cmd_begin(I2C_EXAMPLE_MASTER_NUM, cmd4, 1000 / portTICK_RATE_MS);
      i2c_cmd_link_delete(cmd4);
    }
  }

	void app_main()
	{
		init();				// Initialize stuff
		xTaskCreate(binary, "binary",1024*2, NULL, configMAX_PRIORITIES-1, NULL);
		xTaskCreate(button_press, "button_press",1024*2, NULL, configMAX_PRIORITIES, NULL);
    xTaskCreate(alpha, "alpha",1024*2, NULL, configMAX_PRIORITIES-2, NULL);
	}
