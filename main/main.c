#include <stdio.h>
#include <stdlib.h>

#include "button.h"
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

  xTaskCreate(button_task, "button_task", 2048, NULL, 10, NULL);

  while (1) {
    // ESP_LOGI(TAG, "Main Thread Task");
    vTaskDelay(10 / portTICK_PERIOD_MS);
  }
}