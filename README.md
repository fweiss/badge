# Badge
Badge is a wearable LED matrix display system for communicating visually.

## Hardware
The current prototype is built with a few inexpensive, readily available components. See separate document for details.

## Development
Development is via the Espressif [ESP-IDF](https://github.com/espressif/esp-idf) toolchain. The [Get Started](https://docs.espressif.com/projects/esp-idf/en/stable/get-started/) guide provides all the details
for setting up the toolchain on Windows, Linux, or MacOS.

## Hardware-specific settings
Depending on the hardware, make the following configuraton settings using `idf.py menuconfig`

#### Sparkfun ESP32 Thing
- Component config > ESP32 specific > CPU frequency: 240 MHz
- Component config > ESP32 specific > Main XTAL frequency: 26 MHz
- Serial flasher config > Flash SPI speed: 40 MHz

#### Adafruit ESP32 Huzzah

#### WeMos D1 clone "LOIN32" 
- Component config > ESP32 specific > CPU frequency: 240 MHz
- Component config > ESP32 specific > Main XTAL frequency: 40 MHz
- Serial flasher config > Flash SPI speed: 80 MHz
- Serial flasher config > idf.py monitor baud rate: 115200 bps

USB Silicon Labs CP210x USB to UART bridge

### Old Project Setup
> As of April 2021, much of this is obsoleted.
After the ESP_IDF toolchain is setup, this project can be flashed to an ESP32 device as follows:

- open a command shell
- navigate to this project where it's been cloned from GitHub
- attach the device via USB
- determine the USB device address, depending on the host platform being used (on MacOS, ``/dev/cu.SLAB_USBtoUART``)
- run ``make menuconfig``
- navigate to Serial flasher config > Default serial port
- enter the appropriate serial port and press Enter
- press Q, to update the ESP-IDF project configuration
- run ``make flash``
- a lot of compiling is done the first time
- eventually, the following output indicates the device is flashed: ``Hard resting via RTS pin...``

> Since ESP_IDF 4.4.2, the flash command figures out the COM port on Windows 10.

### Development workflow
Once the project is setup, the following elements comprise the workflow:

- viewing the application log stream
- modifying the code
- flashing the code
- testing the code
- synchronizing (push/pull) with the GitHub repository

### Viewing the application log output
Run the following to view the application log steam ``make monitor``

### Modifying the code
TBD

### Synching with the GitHub repository
TBD

## Client Tools

It is intended that the device wiil be controlled from a mobile phone. For testing, the following tools can be used. There are many other tools with similar capabilities.

### Nordic nRF Connect

Full access to the GATT characteristics.

List of the GATT characteristics: TBD

## Flashing the bin file

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

### Conversation about reliably driving WS2812B with ESP32 RMT with Bluetooth: https://www.reddit.com/r/esp32/comments/e7ixoh/adjust_ble_priority_or_synchronize_advertising/
https://www.esp32.com/viewtopic.php?t=576

### Receive stream data from client
C++ example code: https://openlabpro.com/guide/ble-uart-on-esp32-controller/

### Nordic BLE UART example
https://infocenter.nordicsemi.com/index.jsp?topic=%2Fcom.nordic.infocenter.sdk5.v14.2.0%2Fble_sdk_app_nus_eval.html&cp=4_0_0_4_2_2_22

###Eclipse GDB Hardware Debugging
https://docs.espressif.com/projects/esp-idf/en/latest/api-guides/jtag-debugging/using-debugger.html#jtag-debugging-using-debugger-eclipse

 