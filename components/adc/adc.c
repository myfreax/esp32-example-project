#include "adc.h"

esp_adc_cal_characteristics_t* adc_config(adc1_channel_t adc_channel) {
  ESP_ERROR_CHECK(adc1_config_width(ADC_WIDTH_BIT_DEFAULT));
  ESP_ERROR_CHECK(adc1_config_channel_atten(adc_channel, ADC_ATTEN_DB_11));

  esp_adc_cal_characteristics_t* adc_chars =
      calloc(1, sizeof(esp_adc_cal_characteristics_t));
  esp_adc_cal_characterize(ADC_UNIT_1, ADC_ATTEN_DB_11, ADC_WIDTH_BIT_DEFAULT,
                           1100, adc_chars);
  return adc_chars;
}

uint32_t adc_voltage(adc1_channel_t adc_channel,
                     esp_adc_cal_characteristics_t* adc_chars) {
  uint32_t adc_reading = 0;
  for (int i = 0; i < 64; i++) {
    adc_reading += adc1_get_raw((adc1_channel_t)adc_channel);
  }
  adc_reading /= 64;
  uint32_t voltage = esp_adc_cal_raw_to_voltage(adc_reading, adc_chars);
  return voltage;
}
