#pragma once
#include "esp_err.h"
#include "esp_timer.h"
esp_err_t set_interval(char* name, void* callback, void* callback_params,
                       esp_timer_handle_t* handle, uint64_t us);
esp_err_t set_timeout(char* name, void* callback, void* callback_params,
                      esp_timer_handle_t* handle, uint64_t us);