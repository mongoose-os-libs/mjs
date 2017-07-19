let PWM = {
  // ## **`PWM.set(pin, freq, duty)`**
  // Set and control the PWM. `pin` is a GPIO pin number, `freq` is
  // frequency, in Hz. `freq` 0 disables PWM on the pin. `duty` is duty in %,
  // how long to spend in "1" state. Must be between 0 and 100 inclusive.
  // 0 is "always off", 100 is "always on", 50 is a square wave.
  // Return: true - success, false - failure.
  //
  // Example:
  // ```javascript
  // PWM.set(pin, 50, 2.73);
  // ```
  // Note:
  // on ESP32 we use 8 channels and 4 timers.
  // Each `PWM.set()` call with new pin number assigns a new channel.
  // If we already have a timer running at the specified frequency,
  // we use it instead of assigning a new one.
  set: ffi('bool mgos_pwm_set_double(int, int, double)'),
};
