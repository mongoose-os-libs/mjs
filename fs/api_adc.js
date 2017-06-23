let ADC = {
  // ## **`ADC.enable(pin)`**
  // Configure and enable ADC for a `pin`,
  // return 1 if success, 0 otherwise.
  enable: ffi('int mgos_adc_enable(int)'),
  // ## **`ADC.read(pin)`**
  // Read `pin` analog value, return an integer.
  read: ffi('int mgos_adc_read(int)'),
};
