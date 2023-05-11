#include "button_driver.h"

#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
const static char* TAG = "BUTTON DRIVER";

button_config_t* button_create(unsigned int min_voltage,
                               unsigned int max_voltage,
                               button_callback_t press,
                               button_callback_t lift) {
  button_config_t* button = malloc(sizeof(button_config_t));
  button->state = false;
  button->min_voltage = min_voltage;
  button->max_voltage = max_voltage;
  button->press = press;
  button->lift = lift;
  return button;
}

button_driver_config_t* button_driver_config_create(
    button_config_t** buttons, unsigned char total, bool debug,
    adc1_channel_t adc_channel) {
  buttons_config_t* buttons_config = malloc(sizeof(buttons_config_t));
  buttons_config->total = total;
  buttons_config->buttons = buttons;
  button_driver_config_t* button_driver_config =
      malloc(sizeof(button_driver_config_t));
  button_driver_config->debug = debug;
  button_driver_config->buttons_config = buttons_config;
  button_driver_config->channel = adc_channel;
  return button_driver_config;
}

void button_task(void* arg) {
  button_driver_config_t* button_driver_config = arg;
  buttons_config_t* config = button_driver_config->buttons_config;
  esp_adc_cal_characteristics_t* adc_chars =
      adc_config(button_driver_config->channel);
  while (1) {
    uint32_t voltage = adc_voltage(button_driver_config->channel, adc_chars);
    if (button_driver_config->debug) {
      ESP_LOGI(TAG, "Voltage: %d", voltage);
    }
    for (unsigned char i = 0; i < config->total; i++) {
      button_config_t* button = config->buttons[i];
      if (voltage < button->max_voltage && voltage > button->min_voltage) {
        button->state = true;
        button->press();
      } else {
        if (button->state == true) {
          button->state = false;
          button->lift();
        }
      }
    }
    vTaskDelay(80 / portTICK_PERIOD_MS);
  }
}

void button_driver_install(button_driver_config_t* button_driver_config) {
  xTaskCreate(&button_task, "button_task", 2048, button_driver_config, 10,
              NULL);
}