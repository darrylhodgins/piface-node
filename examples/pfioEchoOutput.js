var pfio = require('../build/Release/pfio');
var EventBus = require('./eventBus');

EventBus.on('pfio.input.changed', function(pin, state) {
	pfio.digital_write(pin, state);
});