"use strict";

var spi = require('./spi');
var Rx = require('rx');

var SPI_WRITE_CMD = 0x40;
var SPI_READ_CMD = 0x41;

// Port configuration
var IODIRA = 0x00; // I/O direction A
var IODIRB = 0x01; // I/O direction B
var IOCON = 0x0A; // I/O config
var GPIOA = 0x12 // port A
var GPIOB = 0x13 // port B
var GPPUA = 0x0C // port A pullups
var GPPUB = 0x0D // port B pullups
var OUTPUT_PORT = GPIOA
var INPUT_PORT = GPIOB

var _outputState = 0x00;

function init() {
	return new Promise(function(resolve, reject) {
		return spi_write(IOCON, 8).then(function() {
			return spi_write(GPIOA, 0x00); // turn on port A
		}).then(function() {
			return spi_write(IODIRA, 0); // set port A as output
		}).then(function() {
			return spi_write(IODIRB, 0xFF); // set port B as input
		}).then(function() {
			return spi_write(GPPUB, 0xFF); // set pullups on port B
		}).catch(reject)
		.then(function() {
			resolve();
		});
	});
}

function deinit() {
}

function spi_write(port, val) {
	return new Promise(function(resolve, reject) {
		return spi.transfer([SPI_WRITE_CMD, port, val]).then(resolve, reject);
	});
}

function spi_read(port) {
	return new Promise(function(resolve, reject) {
		return spi.transfer([SPI_READ_CMD, port, 0xFF]).then(
			function(rxbuf) {
				resolve(rxbuf[2]);
			},
			reject
		);
	});
}

var pinsObservable = Rx.Observable.create(function(observer) {
	setInterval(function() {
		spi_read(INPUT_PORT).then(
			function(val) {
				observer.onNext(val);
			},
			function(e) {
				observer.onError(e);
			}
		);
	}, 500);
});

function digital_read(pin) {
	var mask = (0x01 << pin);
	return Rx.Observable.create(
		function(observer) {
			pinsObservable.subscribe(
				function(val) {
					observer.onNext((val & mask) ? false : true);
				},
				observer.onError,
				observer.onComplete
			);
		}
	);
}

function digital_write(pin, val) {
	if (!val) {
		_outputState &= ~(0x01 << pin);
	} else {
		_outputState |= (0x01 << pin);
	}
	return spi_write(OUTPUT_PORT, _outputState);
}

module.exports = {
	init: init,
	deinit: deinit,
	digital_read: digital_read,
	digital_write: digital_write
}
