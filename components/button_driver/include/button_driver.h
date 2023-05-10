#pragma once
#include <stdbool.h>

#include "adc.h"
typedef void (*button_callback_t)();

typedef struct {
  bool state;
  unsigned int max_vol;
  unsigned int min_vol;
  button_callback_t press;
  button_callback_t lift;
} button_config_t;

typedef struct {
  button_config_t** buttons;
  unsigned char total;
} buttons_config_t;

typedef struct {
  bool debug;
  adc_channel_t channel;
  buttons_config_t* buttons_config;
} button_driver_config_t;

void button_driver_install(button_driver_config_t* button_driver_config);

button_driver_config_t* button_driver_config_create(button_config_t** buttons,
                                                    unsigned char total,
                                                    bool debug,
                                                    adc1_channel_t adc_channel);

button_config_t* button_create(unsigned int min_vol, unsigned int max_vol,
                               button_callback_t press, button_callback_t lift);