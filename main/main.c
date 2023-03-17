

#include <stdio.h>
#include <stdlib.h>

#include "driver/adc.h"
#include "driver/gpio.h"
#include "esp_adc_cal.h"
#include "esp_log.h"
#include "esp_timer.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

static const char* TAG = "ADC";

void app_main(void) {
  adc1_config_width(ADC_WIDTH_BIT_12);
  adc1_config_channel_atten(ADC_CHANNEL_0, ADC_ATTEN_DB_0);
  esp_adc_cal_characteristics_t* adc_chars =
      calloc(1, sizeof(esp_adc_cal_characteristics_t));
  esp_adc_cal_characterize(ADC_UNIT_1, ADC_ATTEN_DB_0, ADC_WIDTH_BIT_12, 1100,
                           adc_chars);
  unsigned char dc_time = 1;
  unsigned char ac_time = 1;
  unsigned char usb_time = 1;
  while (1) {
    uint32_t adc_reading = 0;
    for (int i = 0; i < 64; i++) {
      adc_reading += adc1_get_raw((adc1_channel_t)ADC_CHANNEL_0);
    }
    adc_reading /= 64;
    uint32_t voltage = esp_adc_cal_raw_to_voltage(adc_reading, adc_chars);
    if (voltage < 830 && voltage > 810) {
      vTaskDelay(400 / portTICK_PERIOD_MS);
      ESP_LOGI(TAG, "按下DC按钮: %d, Current voltage: %d", dc_time++, voltage);
    }
    if (voltage < 620 && voltage > 590) {
      vTaskDelay(400 / portTICK_PERIOD_MS);
      ESP_LOGI(TAG, "按下AC按钮: %d, Current voltage: %d", ac_time++, voltage);
    }
    if (voltage < 320 && voltage > 290) {
      vTaskDelay(400 / portTICK_PERIOD_MS);
      ESP_LOGI(TAG, "按下USB按钮: %d, Current voltage: %d", usb_time++,
               voltage);
    }
    vTaskDelay(20 / portTICK_PERIOD_MS);
  }
}