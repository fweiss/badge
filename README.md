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

### ESP82

This is an extremely popular WiFi IoT component. The core element is a 5x5 mm SoC chip that incorporates
WiFi RF transceiver, 802.11 wifi and TCP/IP stack, a fast Tensilica embedded CPU, and 16 GPIO pins for serial
and general purpose I/O. It even has a 10 bit ADC. The chip by itself is not practical for prototyping and
is typically packaged on a PCB with additional support components. For this
project the following packages were evaluated.

- Sparkfun ESP32 Thing
- Adafruit Feather HUZZAH32

## Development Tools

### Eclipse GDB Hardware Debugging

https://docs.espressif.com/projects/esp-idf/en/latest/api-guides/jtag-debugging/using-debugger.html#jtag-debugging-using-debugger-eclipse

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
Following Arduino libraries are needed for this project.

https://github.com/Lucas-Bruder/ESP32_LED_STRIP

## Deployment

Use the ESP_IDF toolchain.

Details TODO

## Client Tools

It is intended that the device wiil be controlled from a mobile phone. For testing, the following tools can be used.

### Nordic Bluetooth Connect

Full access to the GATT characteristics.

Details TODO

## Development

Update firmware on device from bin file.
On Windows.
Download the [ESP GUI](http://espressif.com/en/products/hardware/esp32/resources)

- run "flash_download_tools_vn.n.n"
- select SPIDownload tab
- in first row, click "..."
- navigate to and select "badge.bin" file
- after the "@", enter "0x10000"
- select the checkbox for the first row
- power up the badge device
- connect the device to the computer via USB
- select the COM port
- click Start
- wait until "Finish" is displayed in the Download Panel 1


## Links and References

https://www.esp32.com/viewtopic.php?t=576

Conversation about reliably driving WS2812B with ESP32 RMT with Bluetooth: https://www.reddit.com/r/esp32/comments/e7ixoh/adjust_ble_priority_or_synchronize_advertising/

### Receive stream data from client

C++ example code: https://openlabpro.com/guide/ble-uart-on-esp32-controller/

Nordic BLE UART example: https://infocenter.nordicsemi.com/index.jsp?topic=%2Fcom.nordic.infocenter.sdk5.v14.2.0%2Fble_sdk_app_nus_eval.html&cp=4_0_0_4_2_2_22

 