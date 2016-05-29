# Adafruit Bluefruit Samples

Sample sketches for the Adafruit Feather Bluefruit board.

## blinker

This is a simple blinker. The pin 13 LED is red, next to the USB connector and JST connector.

## bt-blink

This uses the bluetooth UART to control pin 13 by sending a message. When the message is "a", the LED is turned on,
otherwise it is turned off.

Use any bluetooth client, such as Adafruit BLE for Andriod/iOS. Connect in UART mode.
