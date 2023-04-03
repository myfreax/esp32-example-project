#include "led.h"
#include "unity.h"
TEST_CASE("open AC Led", "[led]") { gpio_set_level(LED_AC_PIN, 1); }