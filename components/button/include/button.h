#pragma once
#include <stdbool.h>
#include <stdint.h>

void button_usb_press(int64_t time_us, bool state);
void button_usb_lift(int64_t time_us, bool state);
void button_ac_press(int64_t time_us, bool state);
void button_ac_lift(int64_t time_us, bool state);
void button_dc_press(int64_t time_us, bool state);
void button_dc_lift(int64_t time_us, bool state);