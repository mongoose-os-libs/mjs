/*
 * Copyright (c) 2014-2017 Cesanta Software Limited
 * All rights reserved
 */

#include <esp_sleep.h>

void mgos_esp_deep_sleep_d(double time_in_us) {
  esp_deep_sleep(time_in_us);
}
