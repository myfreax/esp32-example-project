#pragma once

#define LED_USB_PIN 48
#define LED_AC_PIN 38
#define LED_DC_PIN 40
#define LED_PIN_MASK \
  (1ULL << LED_USB_PIN | 1ULL << LED_AC_PIN | 1ULL << LED_DC_PIN)

esp_err_t led_config(uint64_t pin_bit_mask);