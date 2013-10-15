About
=====
Interface to the Raspberry Pi Piface board using Node.js.  This addon shouldn't require any sudo or root privileges to run, as long as your user is in the "spi" group on your Pi (handled by the spidev-setup script).

Note: I've been playing a bit too much with the Pi, so these notes might be missing a few steps.

Installation
============

Get the Piface C libraries
--------------------------
First, you'll need the C libraries, available [here](https://github.com/thomasmacpherson/piface).  Follow the "C" library installation, naturally.

The TL;DR version:
```bash
$ sudo apt-get update
$ sudo apt-get install automake libtool git
$ git clone https://github.com/thomasmacpherson/piface.git
$ cd piface/c
$ ./autogen.sh && ./configure && make && sudo make install
$ sudo ldconfig
$ cd ../scripts
$ sudo ./spidev-setup
```

Get the NPM module
------------------
```bash
$ mkdir ~/my_project
$ cd ~/my_project
$ npm install piface-node
```

A note on running Node.js on the Raspberry Pi
---------------------------------------------
It's not quite as easy to install [Node.js](http://nodejs.org/) on a Raspberry Pi as it is on other platforms, so you might need to dig around to find the newest available version for the Pi's architecture.  At the time I write this, the latest available packaged build for Raspberry Pi is [v0.10.20](http://nodejs.org/dist/v0.10.20/node-v0.10.20-linux-arm-pi.tar.gz).  v0.10.17 and v0.10.20 are the only versions I've tested this on, but if you have success on other versions, please let me know!

```bash
$ wget http://nodejs.org/dist/v0.10.20/node-v0.10.20-linux-arm-pi.tar.gz
$ tar -zxvf node-v0.10.20-linux-arm-pi.tar.gz
$ sudo mkdir /opt/node
$ sudo cp -r node-v0.10.20-linux-arm-pi/* /opt/node
```

You probably don't need the node distribution files after installation, since the important stuff got copied into /opt/node.  I like to remove them, but that's entirely your choice.

Using piface-node
=================
I've intended this to be used with the full awesome power of Node's EventEmitter.  You can easily wire up the physical I/O on the Piface with pretty much anything.

Here's a basic example of the usage, in lieu of actual documentation.  There are also a few examples in the examples folder.

```js
var pfio = require('piface-node');
pfio.init();
pfio.digital_write(0,1); // (pin, state)
var foo = pfio.digital_read(0); // (pin; returns state)
pfio.deinit();
```

```js
var pfio = require('piface-node');
pfio.init();
var foo = pfio.read_input(); // bit-mapped
pfio.write_output(255); // that's binary 11111111, so it'll turn all outputs on.
pfio.deinit();
```
