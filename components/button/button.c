#include "button.h"

#include "adc.h"
#include "buzzer.h"
#include "esp_log.h"
#include "led.h"
static const char* TAG = "BUTTON";

void button_usb_press(int64_t time_us) {
  ESP_LOGI(TAG, "usb button press time: %lld", time_us);
}
void button_usb_lift(int64_t time_us) {
  ESP_LOGI(TAG, "usb button lift time: %lld", time_us);
}
void button_ac_press(int64_t time_us) {
  ESP_LOGI(TAG, "ac button press time: %lld", time_us);
}
void button_ac_lift(int64_t time_us) {
  ESP_LOGI(TAG, "ac button lift time: %lld", time_us);
}
void button_dc_press(int64_t time_us) {
  ESP_LOGI(TAG, "dc button press time: %lld", time_us);
}
void button_dc_lift(int64_t time_us) {
  ESP_LOGI(TAG, "dc button lift time: %lld", time_us);
}