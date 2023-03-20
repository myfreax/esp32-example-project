#include <stdio.h>

#include "driver/gpio.h"

esp_err_t led_config(uint64_t pin_bit_mask) {
  gpio_config_t gpio_conf = {
      .intr_type = GPIO_INTR_DISABLE,
      .mode = GPIO_MODE_OUTPUT,
      .pin_bit_mask = pin_bit_mask,
      .pull_down_en = GPIO_PULLDOWN_ENABLE,
      .pull_up_en = GPIO_PULLUP_ENABLE,
  };
  return gpio_config(&gpio_conf);
}
