/*
 * Copyright (c) 2014-2017 Cesanta Software Limited
 * All rights reserved
 */

#include <user_interface.h>

int mgos_system_deep_sleep_d(double time_in_us) {
  wifi_station_disconnect();
  wifi_set_opmode_current(NULL_MODE);
  return system_deep_sleep(time_in_us);
}
