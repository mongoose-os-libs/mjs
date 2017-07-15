let ESP8266 = {
  // ## **`Sys.deepSleep(microseconds)`**
  // Deep Sleep given number of microseconds.
  // Return value: false on error, otherwise does not return.
  deepSleep:  ffi('int mgos_system_deep_sleep_d(double)'),
};
