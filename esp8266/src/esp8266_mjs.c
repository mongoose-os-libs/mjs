/*
 * Copyright (c) 2014-2017 Cesanta Software Limited
 * All rights reserved
 */

#include <user_interface.h>

int mgos_system_deep_sleep_d(double time_in_us) {
  return system_deep_sleep(time_in_us);
}
