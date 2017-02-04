# Badge

Badge is a wearable LED matrix display system for communicating visually.

## Hardware

The current prototype is built with a few inexpensive, readily available components.

### CJMCU-8x8

This is an inexpensive 8 by 8 RGB LED array based on the WS2812 component.

The front silk screen has "WS28128B-64 RGB LEDS", but note that it's not actually a WS2812B IC, but a WS2812
with 6 pins. This is not really a problem for this project.

The silkscreen on the back shows two sets of three solder pads, but the markings are incorrect (or the silkscreen
is rotated 180 degrees). The +5V and GND are correct, but the DIN and DOUT are reversed. To run the array, connect
the serial input to the DOUT pin.

Current tests. Hue
All green at 150 value: 647 mA

### ESP8266

This is an extremely popular WiFi IoT component. The core element is a 5x5 mm SoC chip that incorporates
WiFi RF transceiver, 802.11 wifi and TCP/IP stack, a fast Tensilica embedded CPU, and 16 GPIO pins for serial
and general purpose I/O. It even has a 10 bit ADC. The chip by itself is not practical for prototyping and
is typically packaged on a PCB with additional support components. For this
project the following packages were evaluated.

- Sparkfun ESP8266 Thing
- Sparkfun ESP8266 Thing Dev
- AI Thinker ESP8266-01
- Olimex MOD ESP8266 DEV

### Adafruit Feather BLE

For evaluating Bluetooth connectivity.

https://learn.adafruit.com/adafruit-feather-m0-bluefruit-le?view=all

## Development Tools

### Arduino IDE 1.6.8

The venerable Arduino IDE is used to compile and upload code to IoT devices. In can be used for a wide variety of
devices and CPUs, not just the original Arduino AVR.

#### Arduino board managers

There are a wide variety of libraries that can be used with the Arduino toolchain.

For ESP8266, see [https://github.com/esp8266/Arduino]. In preferences, add
http://arduino.esp8266.com/stable/package_esp8266com_index.json. Then go to board managers and
install it. Once it's installed, select the appropriate board in the Tools menu.

More info: http://randomnerdtutorials.com/how-to-install-esp8266-board-arduino-ide/

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

#### CP437

The GFX library evidently uses Code Page 437 (CP437). However, the BlueFruit LE client uses UNICODE with UTF-8 encoding.
Without some help, special characters from the Arduino keyboard, such as "ñ" or "®" appear as two or three odd symbols
on the LED matrix. Two transformations are needed.

- UTF-8 to ISO-8859-1/latin1
- ISO-8859-1/latin1 to CP437

It may also be possible to create a custom GFX font that use the ISO-8859-1/latin1 character set.

Another option is to encode CP437 in the client. It's unknown presently if the Arduino keyboard does CP437.

### SPIFFS

On ESP8266, binary files can be uploaded to the flash and read from the program.

[https://github.com/esp8266/Arduino/blob/master/doc/filesystem.md]

### ESP8266WebServer

Handles routing of web requests. Example show use of SPIFFS to serve static content.

[https://github.com/esp8266/Arduino/tree/master/libraries/ESP8266WebServer]

## Deployment

Use the Arduino IDE 1.6.8.

Under Tools, select the correct board.

- Adafruit Feather M0 (Natice USB port)
- etc

## Client Tools

For bluetooth, you'll need a client that can connect and send/receive text.

The preferred client is Adafruit Bluefruit LE.

### Adafruit Bluefruit LE

Multiple connect modes (use UART). Has multiple options.

### nRF UART v2 (Android, iOS)

Work pretty well with the Adafruit Feather M0 Bluetooth. Couldn't configure EOL.

### BlueTerm 1.1

Doesn't connect.

## Bluetooth Serial Port Terminal

Does not pair in SPP.

### Bluetooth Terminal

Does not connect.

### Bluetooth Superterminal

Crashed.

### BT SPP

Requires mac address to connect. No scan.


## Tips

If the Feather M0 gets stuck and the Native USB Port is not accessible from the Arduino IDE, put it into manual bootloader mode.
Press the reset button twice (like a double click) and the red LED will pulse, showing that it's in bootloader mode.
