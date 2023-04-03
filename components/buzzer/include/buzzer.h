#pragma once
#include "esp_err.h"
#define BUZZER_PIN 46

esp_err_t buzzer_config(int BUZZER_GPIO);
esp_err_t buzzer_once(uint64_t time_us);