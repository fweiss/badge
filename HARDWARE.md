# Hardware

The current prototype is built with a few inexpensive, readily available components.

## CJMCU-8x8

This is an inexpensive 8 by 8 RGB LED array based on the WS2812 component.

The front silk screen has "WS28128B-64 RGB LEDS", but note that it's not actually a WS2812B IC, but a WS2812
with 6 pins. This is not really a problem for this project.

The silkscreen on the back shows two sets of three solder pads, but the markings are incorrect (or the silkscreen
is rotated 180 degrees). The +5V and GND are correct, but the DIN and DOUT are reversed. To run the array, connect
the serial input to the DOUT pin.

Current tests. Hue
All green at 150 value: 647 mA

## ESP32

This is an extremely popular WiFi IoT component. The core element is a 5x5 mm SoC chip that incorporates
WiFi RF transceiver, 802.11 wifi and TCP/IP stack, a fast Tensilica embedded CPU, and 16 GPIO pins for serial
and general purpose I/O. It even has a 10 bit ADC. The chip by itself is not practical for prototyping and
is typically packaged on a PCB with additional support components. For this
project the following packages were evaluated.

- Sparkfun ESP32 Thing
- Adafruit Feather HUZZAH32

