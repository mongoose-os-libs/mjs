load('api_gpio.js');
load('api_adc.js');

let Grove = {
  Button: {
    // ## **`Grove.Button.attach(pin, handler)`**
    // Attach a handler for the button on the given pin. Example:
    // ```javascript
    // Grove.Button.attach(pin, function(pin) {
    //    print('Button event at pin', pin);
    // }, null);
    // ```
    attach: function(pin, handler) {
      GPIO.set_button_handler(pin, GPIO.PULL_UP, GPIO.INT_EDGE_NEG, 200,
                              handler, true);
    },
  },
  _motionHandler: undefined,
  MotionSensor: {
    // ## **`Grove.MotionSensor.attach(pin, handler)`**
    // Attach a handler for the motion sensor on the given pin. Example:
    // ```javascript
    // Grove.MotionSensor.attach(pin, function(pin) {
    //    print('Motion sensor event at pin', pin);
    // }, null);
    // ```
    attach: function(pin, handler) {
      GPIO.set_mode(pin, GPIO.MODE_INPUT);
      GPIO.set_int_handler(pin, GPIO.INT_EDGE_POS, handler, null);
      GPIO.enable_int(pin);
      Grove._motionHandler = handler;
    },
  },
  LightSensor: {
    // ## **`Grove.LightSensor.get(pin)`**
    // Not implemented yet
    get: function(pin) {
      return ADC.read(pin);
    },
  },
  MoistureSensor: {
    // ## **`Grove.MoistureSensor.get(pin)`**
    // Not implemented yet
    get: function(pin) {
      return ADC.read(pin);
    },
  },
  UVSensor: {
    // ## **`Grove.MoistureSensor.get(pin)`**
    // Not implemented yet
    get: function(pin) {
      return ADC.read(pin);
    },
  },
  _relayInited: undefined,
  _relayClosed: 0,
  Relay: {
    _init: function(pin) {
      if (Grove._relayInited !== 1) {
        GPIO.set_mode(pin, GPIO.MODE_OUTPUT);
        GPIO.set_pull(pin, GPIO.PULL_DOWN);
        Grove._relayInited = 1;
      }
    },

    // ## **`Grove.Relay.open(pin)`**
    // Open relay at the given pin.
    open: function(pin) {
      this._init(pin);
      GPIO.write(pin, 0);
      Grove._relayClosed = 0;
    },

    // ## **`Grove.Relay.close(pin)`**
    // Close relay at the given pin.
    close: function(pin) {
      this._init(pin);
      GPIO.write(pin, 1);
      Grove._relayClosed = 1;
    },

    // ## **`Grove.Relay.isClosed(pin)`**
    // Returns 0 if relay is opened, or 1 if it's closed.
    isClosed: function(pin) {
      return Grove._relayClosed;
    },
  },
};
