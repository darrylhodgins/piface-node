Sorry, this documentation is currently incomplete.  I went through a bit of trial and error to get things going myself, and some of the dependencies aren't listed.

About
=====
Interface to the Raspberry Pi Piface board using Node.js.  This addon shouldn't require any sudo or root privileges to run, as long as your user is in the "spi" group on your Pi.

Dependencies
============

piface
------
Everything piface, availble [here](https://github.com/thomasmacpherson/piface).  Follow the "C" library installation.

Node.js
-------
You'll need [Node.js](http://nodejs.org/), of course.  It's not quite as easy to install on a Raspberry Pi as it is on other platforms, so you might need to dig around to find the newest available version for the Pi's architecture.  At the time I write this, the latest available packaged build for Raspberry Pi is [v0.10.17](http://nodejs.org/dist/v0.10.17/node-v0.10.17-linux-arm-pi.tar.gz).

Node-Gyp
--------
Build tool for Node.js addons.  You can find it [here](https://github.com/TooTallNate/node-gyp).

Installation of piface-node
===========================
```bash
$ node-gyp configure
$ node-gyp build
```

Using piface-node
=================

Something along these lines should do it:

```js
var pfio = require('/path/to/build/Release/pfio');
pfio.init();
pfio.digital_write(0,1);
pfio.deinit();
```

