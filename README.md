# Badge

Badge is a wearable LED matrix display system for communicating visually.

## Tools

### glediator

This is a graphical LED array composer and mixer. Is has several built-in patterns and effects. It can fade between
two programs. It can also render animated GIFs.

In its typical use case, it's connected to an LED array for light shows. It can also record a binary stream of RGB
values that can be exported and played back later or looped.

### Arduino

The venerable Arduino IDE is used to compile and upload code to IoT devices. In can be used for a wide variety of
devices and CPUs, not just the original Arduino AVR.

There are a wide variety of libraries that can be used with the Arduino toolchain.

## Libraries

#### fastled

#### Adafruit NeoPixel

https://github.com/adafruit/Adafruit_NeoPixel

## Hardware

### CJMCU-8x8

This is an inexpensive 8 by 8 array based on WS2812 LEDs.

The front silk screen has "WS28128B-64 RGB LEDS", but note that it's not actually a WS2812B IC, but a WS2812
with 6 pins. This is not really a problem for this project.

The silkscreen on the back shows two sets of three solder pads, but the markings are incorrect (or the silkscreen
is rotated 180 degrees). The +5V and GND are correct, but the DIN and DOUT are reversed. To run the array, connect
the serial input to the DOUT pin.

Current tests. Hue
All green at 150 value: 647 mA



