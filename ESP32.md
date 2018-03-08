# ESP32 notes
There are currently two ESP32 toolchains:

- ESP-IDF from Espressif
- Arduino-ESP

In addition, there is the Eclipse CDT and Sloeber.

Here I will explore the options. Ideally, I want to do ESP32 development in Eclipse-CDT-Sloeber.
I also hope to use the Adafruit Neopixel libraries.

## Options for developing for ESP32
The quesions boils down to:
- Arduino or ESP-IDF? Neopixel support?
- Arduino IDE/ESP-IDF or Eclipse? Well, Eclipse for sure!
- Sloeber or just CDT? Sloeber supports all Arduino
- Dual toolchain? I'm happy not using ArduinoIDE at all, but can I convince collaborators?

### ESP-IDF
This has the best Espressif support. It's command line based. On windows it use MSYS. 
Project setup is via a GUI called menuconfig, which is launched with the make command.

### arduino-esp32
This is a community project which is reaching parity with ESP-IDF. It probably has the best chance of integrating with
Adafruit Neopixel libraries.

### Eclipse + ESP-IDF
This is pretty easy to do. See youtube link below.

### Ecplise + Sloeber
Does this work with arduino-esp32?

## Links and references
https://www.youtube.com/watch?v=bYh2w0HzS7s&t=65s
