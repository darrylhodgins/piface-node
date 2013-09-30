var pfio = require('../build/Release/pfio');
var EventBus = require('./eventBus');

var prev_state = [];

// Watch for Ctrl+C
process.on('SIGINT', stopListening);

// Main busy loop uses setTimeout internally, rather than setInterval.  It was because I had
// different delays in different cases, but I don't think it really matters a whole lot either
// way.
startListening();

function startListening() {
	pfio.init();
	watchInputs();
}

function stopListening() {
	pfio.deinit();
	process.exit(0);
}

// Watches for state changes
function watchInputs() {
	var state;
	for (var pin = 0; pin < 8; pin++) {
		state = pfio.digital_read(pin);
		if (state !== prev_state[pin]) {
			prev_state[pin] = state;
			EventBus.emit('pfio.input.changed', pin, state);
		}
	}
	setTimeout(watchInputs, 10);
}
