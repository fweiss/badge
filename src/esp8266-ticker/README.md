# ESP8266 Ticker

This provides the capability of displaying a line of scrolling text and setting the text from a smart phone
via WiFi.

## Hardware

This requires an ESP8266-based device. It was tested with a Sparkfun ESP8266 Thing Dev device. It ought to run on any
device which uses the ESP8266 chip.

## WiFi connection

On the smart phone, look for an access point that starts with "ESP8266 Thing". Connect using the password "sparkfun".

## Changing the text

Open this url from the smart phone: [http://192.168.4.1]. The browser will display a text box and a submit button.

Tap the text box and enter a message. Click Submit. The message you entered will be displayed on the ticker.

## TODO

Thinking of adding these capabilities:

- changing text color
- changing background
- saving a list of messages
- adding emoticons
- display submitted text to allow editing
