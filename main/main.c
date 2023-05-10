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

static const char* TAG = "ADC";

void app_main(void) {
  ESP_ERROR_CHECK(led_config(LED_PIN_MASK));
  ESP_ERROR_CHECK(buzzer_config(BUZZER_PIN));

  button_config_t* usb_button =
      button_create(279, 569, &button_usb_press, &button_usb_lift);
  button_config_t* ac_button =
      button_create(569, 586, &button_ac_press, &button_ac_lift);
  button_config_t* dc_button =
      button_create(789, 802, &button_dc_press, &button_dc_lift);

  button_config_t* buttons[3] = {usb_button, ac_button, dc_button};

  button_driver_config_t* button_driver_config = button_driver_config_create(
      buttons, sizeof(buttons) / sizeof(button_config_t*), false,
      ADC1_CHANNEL_0);

  button_driver_install(button_driver_config);

  while (1) {
    ESP_LOGI(TAG, "Main Thread Task");
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}