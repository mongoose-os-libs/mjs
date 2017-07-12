let ESP8266 = {
  // ## **`Sys.deepSleep(microseconds)`**
  // Deep Sleep given number of microseconds.
  // Return value: false on error.
  deepSleep:  ffi('int mgos_system_deep_sleep_d(double)'),
};
