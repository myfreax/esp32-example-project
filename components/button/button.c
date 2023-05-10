#include "button.h"

#include "adc.h"
#include "buzzer.h"
#include "esp_log.h"
#include "led.h"
static const char* TAG = "BUTTON";

void button_usb_press() { ESP_LOGI(TAG, "usb button press"); }
void button_usb_lift() { ESP_LOGI(TAG, "usb button lift"); }
void button_ac_press() { ESP_LOGI(TAG, "ac button press"); }
void button_ac_lift() { ESP_LOGI(TAG, "ac button lift"); }
void button_dc_press() { ESP_LOGI(TAG, "dc button press"); }
void button_dc_lift() { ESP_LOGI(TAG, "dc button lift"); }