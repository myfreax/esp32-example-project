#include "buzzer.h"
#include "driver/adc.h"
#include "esp_adc_cal.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "led.h"

static const char* TAG = "ADC";

void button_task(void* arg) {
  // init adc
  ESP_ERROR_CHECK(adc1_config_width(ADC_WIDTH_BIT_12));
  ESP_ERROR_CHECK(adc1_config_channel_atten(ADC_CHANNEL_0, ADC_ATTEN_DB_0));
  esp_adc_cal_characteristics_t* adc_chars =
      calloc(1, sizeof(esp_adc_cal_characteristics_t));
  esp_adc_cal_characterize(ADC_UNIT_1, ADC_ATTEN_DB_0, ADC_WIDTH_BIT_12, 1100,
                           adc_chars);

  // button state
  unsigned char dc_button_state = 0;
  unsigned char ac_key_state = 0;
  unsigned char usb_key_state = 0;

  // read adc voltage
  while (1) {
    uint32_t adc_reading = 0;
    for (int i = 0; i < 64; i++) {
      adc_reading += adc1_get_raw((adc1_channel_t)ADC_CHANNEL_0);
    }
    adc_reading /= 64;
    uint32_t voltage = esp_adc_cal_raw_to_voltage(adc_reading, adc_chars);
    // ESP_LOGI(TAG, "Voltage: %d", voltage);
    if (voltage < 820 && voltage > 802) {
      vTaskDelay(200 / portTICK_PERIOD_MS);
      if (dc_button_state == 0) {
        dc_button_state = 1;
      } else {
        dc_button_state = 0;
      }
      ESP_ERROR_CHECK(gpio_set_level(LED_DC_PIN, dc_button_state));
      ESP_ERROR_CHECK(buzzer_once(100 * 1000));
      ESP_LOGI(TAG, "DC Button State: %d, Current voltage: %d", dc_button_state,
               voltage);
    }
    if (voltage < 758 && voltage > 576) {
      vTaskDelay(200 / portTICK_PERIOD_MS);
      if (ac_key_state == 0) {
        ac_key_state = 1;
      } else {
        ac_key_state = 0;
      }
      ESP_ERROR_CHECK(gpio_set_level(LED_AC_PIN, ac_key_state));
      ESP_ERROR_CHECK(buzzer_once(100 * 1000));
      ESP_LOGI(TAG, "AC Button State: %s, Current voltage: %d",
               ac_key_state ? "On" : "Off", voltage);
    }
    if (voltage < 320 && voltage > 289) {
      vTaskDelay(200 / portTICK_PERIOD_MS);
      if (usb_key_state == 0) {
        usb_key_state = 1;
      } else {
        usb_key_state = 0;
      }
      ESP_ERROR_CHECK(gpio_set_level(LED_USB_PIN, usb_key_state));
      ESP_ERROR_CHECK(buzzer_once(100 * 1000));
      ESP_LOGI(TAG, "USB Button State: %d, Current voltage: %d", usb_key_state,
               voltage);
    }
    vTaskDelay(100 / portTICK_PERIOD_MS);
  }
}