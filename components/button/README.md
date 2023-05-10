```c
  while (1) {
    uint32_t voltage = adc_voltage(ADC_CHANNEL_0, adc_chars);
    // ESP_LOGI(TAG, "Voltage: %d", voltage);
    // if (voltage < 797 && voltage > 789) {
    //   if (dc_button_state == 0) {
    //     dc_button_state = 1;
    //   } else {
    //     dc_button_state = 0;
    //   }
    //   ESP_ERROR_CHECK(gpio_set_level(LED_DC_PIN, dc_button_state));
    //   ESP_LOGI(TAG, "Enter DC Voltage: %d", voltage);
    // }

    // AC Button
    if (voltage < 586 && voltage > 569) {
      ac_button_is_press = true;
      // emit press event
      ESP_LOGI(TAG, "Usb Button Pressed and Voltage: %d", voltage);
    } else {
      if (ac_button_is_press == true) {
        ac_button_is_press = false;
        ESP_LOGI(TAG, "uplift");
        // emit uplift event
        // for debug
        if (ac_button_state == 0) {
          ac_button_state = 1;
        } else {
          ac_button_state = 0;
        }
        ESP_ERROR_CHECK(gpio_set_level(LED_AC_PIN, ac_button_state));
        // for debug
      }
    }

    // USB Button
    if (voltage < 569 && voltage > 279) {
      usb_button_is_press = true;
      ESP_LOGI(TAG, "Usb Button Pressed and Voltage: %d", voltage);
    } else {
      if (usb_button_is_press == true) {
        usb_button_is_press = false;
        ESP_LOGI(TAG, "uplift");
        // emit uplift event
        // for debug
        if (usb_button_state == 0) {
          usb_button_state = 1;
        } else {
          usb_button_state = 0;
        }
        ESP_ERROR_CHECK(gpio_set_level(LED_USB_PIN, usb_button_state));
        // for debug
      }
    }
    vTaskDelay(80 / portTICK_PERIOD_MS);
  }
```