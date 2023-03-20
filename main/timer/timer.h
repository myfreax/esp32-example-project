#pragma once
#include "esp_timer.h"

void set_interval(char* name, void* callback, void* callback_params,
                  esp_timer_handle_t* handle, uint64_t us);
void set_timeout(char* name, void* callback, void* callback_params,
                 esp_timer_handle_t* handle, uint64_t us);
void clear_interval(esp_timer_handle_t timer);
void clear_timeout(esp_timer_handle_t timer);