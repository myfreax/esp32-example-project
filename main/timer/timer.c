#include "timer.h"

#include <stdio.h>
#include <string.h>

#include "sdkconfig.h"

void set_interval(char* name, void* callback, void* callback_params,
                  esp_timer_handle_t* handle, uint64_t us) {
  const esp_timer_create_args_t args = {
      .callback = callback, .arg = callback_params, .name = name};
  ESP_ERROR_CHECK(esp_timer_create(&args, handle));
  ESP_ERROR_CHECK(esp_timer_start_periodic(*handle, us));
}

void set_timeout(char* name, void* callback, void* callback_params,
                 esp_timer_handle_t* handle, uint64_t us) {
  const esp_timer_create_args_t args = {
      .callback = callback, .arg = callback_params, .name = name};
  ESP_ERROR_CHECK(esp_timer_create(&args, handle));
  ESP_ERROR_CHECK(esp_timer_start_once(*handle, us));
}

void clear_interval(esp_timer_handle_t timer) {
  ESP_ERROR_CHECK(esp_timer_delete(timer));
}

void clear_timeout(esp_timer_handle_t timer) {
  ESP_ERROR_CHECK(esp_timer_delete(timer));
}
