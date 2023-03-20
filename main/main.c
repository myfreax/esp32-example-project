

#include <stdio.h>
#include <stdlib.h>

#include "adc/adc.h"
#include "buzzer/buzzer.h"
#include "driver/adc.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "led/led.h"

static const char* TAG = "ADC";

void app_main(void) {
  ESP_ERROR_CHECK(led_config(LED_PIN_MASK));
  ESP_ERROR_CHECK(buzzer_config(BUZZER_PIN));

  xTaskCreate(adc_button_task, "adc_button_task", 2048, NULL, 10, NULL);

  while (1) {
    ESP_LOGI(TAG, "Main Thread Task");
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}