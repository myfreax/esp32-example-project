#include "button.h"

#include "buzzer.h"
#include "esp_log.h"
#include "led.h"

static const char* TAG = "BUTTON";

void button_usb_press(int64_t time_us, bool state, uint32_t voltage) {
  ESP_LOGI(TAG, "usb button press time: %lld state: %d", time_us, state);
}

void button_usb_lift(int64_t time_us, bool state, uint32_t voltage) {
  ESP_LOGI(TAG, "usb button lift time: %lld state: %d", time_us, state);
  gpio_set_level(CONFIG_LED_USB_PIN, state);
  buzzer_once(100 * 1000);
}

void button_ac_press(int64_t time_us, bool state, uint32_t voltage) {
  ESP_LOGI(TAG, "ac button press time: %lld state: %d", time_us, state);
}

void button_ac_lift(int64_t time_us, bool state, uint32_t voltage) {
  ESP_LOGI(TAG, "ac button lift time: %lld state: %d", time_us, state);
  gpio_set_level(CONFIG_LED_AC_PIN, state);
  buzzer_once(100 * 1000);
}

void button_dc_press(int64_t time_us, bool state, uint32_t voltage) {
  ESP_LOGI(TAG, "dc button press time: %lld state: %d", time_us, state);
}

void button_dc_lift(int64_t time_us, bool state, uint32_t voltage) {
  ESP_LOGI(TAG, "dc button lift time: %lld state: %d", time_us, state);
  gpio_set_level(CONFIG_LED_DC_PIN, state);
  buzzer_once(100 * 1000);
}