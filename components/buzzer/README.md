# buzzer
Universal Buzzer Assembly

## Usage
```c
#include "buzzer.h"

void app_main(void) {
  ESP_ERROR_CHECK(buzzer_config(BUZZER_PIN));
  
  buzzer_once(100 * 1000);
}
```