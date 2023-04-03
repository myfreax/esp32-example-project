#include "timer.h"

esp_err_t set_interval(char* name, void* callback, void* callback_params,
                       esp_timer_handle_t* handle, uint64_t us) {
  esp_err_t err;
  const esp_timer_create_args_t args = {
      .callback = callback, .arg = callback_params, .name = name};
  err = esp_timer_create(&args, handle);
  if (err != ESP_OK) {
    return err;
  }
  esp_timer_start_periodic(*handle, us);
  if (err != ESP_OK) {
    return err;
  }
  return ESP_OK;
}

esp_err_t set_timeout(char* name, void* callback, void* callback_params,
                      esp_timer_handle_t* handle, uint64_t us) {
  esp_err_t err;
  const esp_timer_create_args_t args = {
      .callback = callback, .arg = callback_params, .name = name};

  err = esp_timer_create(&args, handle);
  if (err != ESP_OK) {
    return err;
  }
  err = esp_timer_start_once(*handle, us);
  if (err != ESP_OK) {
    return err;
  }
  return ESP_OK;
}