# Badge

Badge is a wearable LED matrix display system for communicating visually.

## Tools

### Arduino IDE 1.6.8

The venerable Arduino IDE is used to compile and upload code to IoT devices. In can be used for a wide variety of
devices and CPUs, not just the original Arduino AVR.

#### Arduino board managers

There are a wide variety of libraries that can be used with the Arduino toolchain.

For ESP8266, see [https://github.com/esp8266/Arduino]. In preferences, add
http://arduino.esp8266.com/stable/package_esp8266com_index.json. Then go to board managers and
install it. Once it's installed, select the appropriate board in the Tools menu.

#### Arduino ESP8266FS plugin

This plugin allows you upload data files to the ESP8266 flash from the Arduino IDE.

[https://github.com/esp8266/arduino-esp8266fs-plugin]

This will not work with the Sparkfun Thing, which has only 512 kB flash.

#### C++11

A number of examples in this project use array initializers. You need to enable C++11 in your Arduino toolchain.

In arduino/hardware/arduino/avr, in the platform.txt file, add "-std=gnu++11 to the end of the property
compiler.cpp.flags

Additional info about initializers in C++11: http://www.informit.com/articles/article.aspx?p=1852519

### glediator

This is a graphical LED array composer and mixer. Is has several built-in patterns and effects. It can fade between
two programs. It can also render animated GIFs.

In its typical use case, it's connected to an LED array for light shows. It can also record a binary stream of RGB
values that can be exported and played back later or looped.


## Libraries

### FastLED

This is a pretty clean library that handles a lot of pixel hardware. Unfortunately, it is not yet ready for ESP8266.

### Adafruit NeoPixel libraries

https://github.com/adafruit/Adafruit_NeoPixel

plus matrix, gfx

https://learn.adafruit.com/adafruit-gfx-graphics-library/overview

### SPIFFS

On ESP8266, binary files can be uploaded to the flash and read from the program.

[https://github.com/esp8266/Arduino/blob/master/doc/filesystem.md]

### ESP8266WebServer

Handles routing of web requests. Example show use of SPIFFS to serve static content.

[https://github.com/esp8266/Arduino/tree/master/libraries/ESP8266WebServer]

## Hardware

### ESP8266

to use the arduino toolchain, add the board manager in preferencs

http://arduino.esp8266.com/stable/package_esp8266com_index.json

go to the boards manager, select, and install.

mor info: http://randomnerdtutorials.com/how-to-install-esp8266-board-arduino-ide/

### CJMCU-8x8

This is an inexpensive 8 by 8 array based on WS2812 LEDs.

The front silk screen has "WS28128B-64 RGB LEDS", but note that it's not actually a WS2812B IC, but a WS2812
with 6 pins. This is not really a problem for this project.

The silkscreen on the back shows two sets of three solder pads, but the markings are incorrect (or the silkscreen
is rotated 180 degrees). The +5V and GND are correct, but the DIN and DOUT are reversed. To run the array, connect
the serial input to the DOUT pin.

Current tests. Hue
All green at 150 value: 647 mA



