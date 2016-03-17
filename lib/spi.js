"use strict";

var SPI = require('pi-spi');

var spi = SPI.initialize('/dev/spidev0.0');
spi.clockSpeed(1e6);

function spi_transfer(txbuffer) {
	var txbuf = new Buffer(txbuffer);

	return new Promise(function(resolve, reject) {
		setTimeout(
			function() {
				spi.transfer(txbuf, function(device, buf) {
					resolve(buf);
				});
			},
			50
		);
	});
}

module.exports = {
	transfer: spi_transfer
}

