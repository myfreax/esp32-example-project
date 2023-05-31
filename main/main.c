#include <stdio.h>
#include <stdlib.h>

#include "button.h"
#include "button_driver.h"
#include "buzzer.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "led.h"
#include "timer.h"

static const char* TAG = "ESP32-EXAMPLE-PROJECT";

void app_main(void) {
  ESP_ERROR_CHECK(led_config(1ULL << CONFIG_LED_USB_PIN |
                             1ULL << CONFIG_LED_AC_PIN |
                             1ULL << CONFIG_LED_DC_PIN));
  ESP_ERROR_CHECK(buzzer_config(46));

  unsigned char custom_parameter = 1;
  button_config_t* usb_button = button_create(
      0, 279, 569, &button_usb_press, &button_usb_lift, &custom_parameter);
  button_config_t* ac_button =
      button_create(1, 569, 586, &button_ac_press, &button_ac_lift, NULL);
  button_config_t* dc_button =
      button_create(1, 789, 802, NULL, &button_dc_lift, NULL);

  button_config_t* buttons[3] = {usb_button, ac_button, dc_button};

  button_driver_config_t* button_driver_config = button_driver_config_create(
      buttons, sizeof(buttons) / sizeof(button_config_t*), ADC1_CHANNEL_0);

  button_driver_install(button_driver_config, 2048);

  while (1) {
    ESP_LOGI(TAG, "Main Thread Task");
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}