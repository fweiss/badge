# Bugs
Current bugs that are being resolved

## Long startup after fixing led glitching bug
This was resolved by initializing RMT in a task pinned to APP core.
Originally, RMT was initialized via app_main, which was running on PRO core.
The app_main function now starts a pinned task to initialize the app.

Status: (BT-bluetooth, BD=bluedroid, AT=AnimationTask)
- run BT and BD on APP stops glitching, but adds HCI timeout error
- changing AT core doesn't seem to matter
- changing RMT wait_tx_done doesn't seem to matter
- reduce ``rmt_write_sample`` size from 64*3 to 64*1 stops glitching
- reduce to size from 64 to 60 still glitches
- 32: OK, 48: OK, 56: OK, 60: glitch see note below
- 56 does glitch, but not on scope, because no output at LED 64
- @64, DO(64) length is 80 or 160 us, so 64 or 128 bits

Leds were glitching so made both bluetooth and bluedroid run on core 1.

That fixed the glitch, apparently removing some ISR interfernce.

But now during boot there's

``E (9595) BT_HCI: command_timed_out hci layer timeout waiting for response to a command. opcode: 0xc03``

0xc03 = reset command?

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

turn debugging on for HCI (W -> D)

``D (1419) BT_HCI: btu_free_timer Unable to find expected alarm in hashmap``

switching wifi to app cpu changed nothing

trying bt/bdroid/wifi on pro cpu and rmt on app cpu

## Checkpoint

1)
with bt/bdroid/wifi pinned to PRO
with AnimationTask either PRO or APP
then glitching

2)
with bt/bdroid/wifi pinned to APP
timeout on HCI command 0xc03
no glitching

3a) with only bt on APP, AT on PRO
no timeout
no glitching?

3b) bt on APP, AT on APP
timeout
glitch

4) with only bdroid on app
no timeout
glitches




