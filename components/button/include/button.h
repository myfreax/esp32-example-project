#pragma once
#include <stdint.h>
void button_usb_press(int64_t time_us);
void button_usb_lift(int64_t time_us);
void button_ac_press(int64_t time_us);
void button_ac_lift(int64_t time_us);
void button_dc_press(int64_t time_us);
void button_dc_lift(int64_t time_us);