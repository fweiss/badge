# Bugs
Current bugs that are being resolved

## Long startup after fixing led glitching bug
Leds were glitching so made both bluetooth and bluedroid run on core 1.
That fixed the glitch, apparently removing some ISR interfernce.

But now during boot there's

``E (9595) BT_HCI: command_timed_out hci layer timeout waiting for response to a command. opcode: 0xc03``

this is bracketed by
``I (1065) BADGE: initializing``
and
``I (61625) BLECore: bluetooth device address: 30:ae:a4:22:dd:8a``
note the long delay

looks like this happens on BLECore::initDevice
probably ``esp_bluedroid_enable``

boot log shows chip revision 1
try changeing  Component config > ESP32-specific > Minimum Supported ESP32 Revision
from 0 to 1

[Pro and App CPU](https://www.esp32.com/viewtopic.php?t=8558)

check these:


one tip is each core has a separate scheduler
but what about interrupts?
