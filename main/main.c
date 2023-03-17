

#include <stdio.h>
#include <stdlib.h>

#include "driver/adc.h"
#include "driver/gpio.h"
#include "esp_adc_cal.h"
#include "esp_log.h"
#include "esp_timer.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define LED_USB 48
#define LED_AC 38
#define LED_DC 40
#define KEY_LED_MASK (1ULL << LED_USB | 1ULL << LED_AC | 1ULL << LED_DC)

static const char* TAG = "ADC";

void adc_key_task(void* arg) {
  // GPIO
  gpio_config_t gpio_conf = {
      .intr_type = GPIO_INTR_DISABLE,
      .mode = GPIO_MODE_OUTPUT,
      .pin_bit_mask = KEY_LED_MASK,
      .pull_down_en = GPIO_PULLDOWN_ENABLE,
      .pull_up_en = GPIO_PULLUP_ONLY,
  };
  gpio_config(&gpio_conf);
  // ADC
  adc1_config_width(ADC_WIDTH_BIT_12);
  adc1_config_channel_atten(ADC_CHANNEL_0, ADC_ATTEN_DB_0);
  esp_adc_cal_characteristics_t* adc_chars =
      calloc(1, sizeof(esp_adc_cal_characteristics_t));
  esp_adc_cal_characterize(ADC_UNIT_1, ADC_ATTEN_DB_0, ADC_WIDTH_BIT_12, 1100,
                           adc_chars);
  unsigned char dc_key_state = 0;
  unsigned char ac_key_state = 0;
  unsigned char usb_key_state = 0;
  while (1) {
    uint32_t adc_reading = 0;
    for (int i = 0; i < 64; i++) {
      adc_reading += adc1_get_raw((adc1_channel_t)ADC_CHANNEL_0);
    }
    adc_reading /= 64;
    uint32_t voltage = esp_adc_cal_raw_to_voltage(adc_reading, adc_chars);
    if (voltage < 830 && voltage > 810) {
      vTaskDelay(400 / portTICK_PERIOD_MS);
      ESP_LOGI(TAG, "DC Key State: %d, Current voltage: %d", dc_key_state,
               voltage);
      if (dc_key_state == 0) {
        dc_key_state = 1;
      } else {
        dc_key_state = 0;
      }
      gpio_set_level(LED_DC, dc_key_state);
    }
    if (voltage < 620 && voltage > 590) {
      vTaskDelay(400 / portTICK_PERIOD_MS);
      ESP_LOGI(TAG, "AC Key State: %d, Current voltage: %d", ac_key_state,
               voltage);
      if (ac_key_state == 0) {
        ac_key_state = 1;
      } else {
        ac_key_state = 0;
      }
      gpio_set_level(LED_AC, ac_key_state);
    }
    if (voltage < 320 && voltage > 290) {
      vTaskDelay(400 / portTICK_PERIOD_MS);
      ESP_LOGI(TAG, "USB Key State: %d, Current voltage: %d", usb_key_state,
               voltage);
      if (usb_key_state == 0) {
        usb_key_state = 1;
      } else {
        usb_key_state = 0;
      }
      gpio_set_level(LED_USB, usb_key_state);
    }
    vTaskDelay(20 / portTICK_PERIOD_MS);
  }
}
void app_main(void) {
  xTaskCreate(adc_key_task, "adc_key_task", 2048, NULL, 10, NULL);
  while (1) {
    ESP_LOGI(TAG, "Main Thread Task");
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}