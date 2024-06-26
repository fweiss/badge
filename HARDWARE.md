# Hardware
The current prototype is built with a few inexpensive, readily available components.

- CJMCU-8x8 CJMCU-8x8 array
- MPU6050 IMU
- ESP32 LiPo dev board
- LiPo battery

## CJMCU-8x8
This is an inexpensive 8 by 8 RGB LED array based on the WS2812 component.

> Current display uses WS2812B 4-pin neopixels and has the corrected silk screen.

The front silk screen has "WS28128B-64 RGB LEDS", but note that it's not actually a WS2812B IC, but a WS2812
with 6 pins. This is not really a problem for this project.

The silkscreen on the back shows two sets of three solder pads, but the markings are incorrect (or the silkscreen
is rotated 180 degrees). The +5V and GND are correct, but the DIN and DOUT are reversed. To run the array, connect
the serial input to the DOUT pin.

Current tests. Hue
All green at 150 value: 647 mA

## WS2812 addressable RGB LED
This is the older 6-pin version of the 4-pin WS2812.
- 400 kps data transmission rate, 2.5 us
- 0 code high 350 ns low 800 ns
- 1 code high 700 ns low 600 ns
- tolerance +/- 150 ns
- reset > 50 us

### Orientation and addressing
The display is zig-zag. Looking at the fron of the display, the first pixel is at the
top left, pixel 8 is at the left of the second row, and so forth.

## ESP32

This is an extremely popular WiFi IoT component. The core element is a 5x5 mm SoC chip that incorporates
WiFi RF transceiver, 802.11 wifi and TCP/IP stack, a fast Tensilica embedded CPU, and 16 GPIO pins for serial
and general purpose I/O. It even has a 10 bit ADC. The chip by itself is not practical for prototyping and
is typically packaged on a PCB with additional support components. For this
project the following packages were evaluated.

- Sparkfun ESP32 Thing
- Adafruit Feather HUZZAH32

# MPU6050
### Orientation
Reference USB at right top of device.

X axis = right
Y axis = top
Z axis = up

using the dlpf at 5 Hz, there's a slight signal that oscillates some of the leds
it may be at 2.5 hz
Turned out to be the drop limit was < 0.1
changing to < fixed it

## Links and references
[WS2812 datasheet](https://cdn-shop.adafruit.com/datasheets/WS2812.pdf)