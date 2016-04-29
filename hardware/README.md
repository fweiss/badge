# Hardware

This is all about hardware components for badge.

## Design limits

This is a WIP. The design limits are still being developed and tested.

### Assumptions

* It should use an 8 x 8 (64 total) array of RGB LEDS.
* It should be wearable in a breast pocket.
* It must be as portable as a smart phone.
* It could be networked with a smartphone.
* The LEDs should be addressed simply, as by a WS28xx-like serial shift register.
* The LED array must not get hot to the touch.
* The LEDs could be WS2812, APA104, etc.
* Any prototype parts list should be less than $200.
* Programming could be via Arduino toolchain.

### Conclusions

#### Heat constraint

The LED array component can produce more heat than is tolerable to touch by a human. This was discovered after testing.
The Power sketch provide details.

This was not an originally important assumption. Early testing exposed it as an important constraint.

## Component review

This is a place to get specs for components that have been evaluated.

## Rev4000 (power source)

Abundant charge, clunky 13.2 mm thick, inexpensive. Could use with smaller LiPo cell and use extra space in the case for components?

* Capacity: 4000 mAh
* Input: 2000mA @ 5 V
* Output: 2400 mA @ 5 V (split outlets)
* Peak current: ??
* Size: 100 x 66 x 13 (mm)
* Weight:
* Extra: charge % display, satin charcoal aluminum case

20160326 $17.99 @ Bestbuy

### Antec LifeCard 2000 (power source)

It's very thin, 6 mm. It's not expensive.

* Capacity: 2000 mAh
* Input: 600 mA @ 5 V
* Output: 1000 mA @ 5 V
* Size: 86 x 64 x 6 (mm)
* Weight: 49 g

20160326 $14.95 @ Central Computers*

## Antec Lifebar

This is the one that Mike got.

## Sparkfun ESP8266 Thing Dev

Highly integrated WiFi, CPU, and I/O. built in FTDI and micro USB, built-in 3.3 V regulator, pass-through 5V.

Development is eased by being able to program over micro-USB directly with the integrated FTDI chip.

## Adafruit Feather 32u4 Bluefruit LE

Highly integrated ATmega32u4, MDBT40 bluetooth, LiPo charger.

20160328 $29.95 @ Adafruit (out of stock)

## Olimex MOD-ESP8266-DEV

This is a basic ESP8266+flash development board. It's smaller that either of the Sparkfun boards,
yet exposes all the ESP8266 I/O pins with 2.54 mm pitch through holes. It's a bit harder to program, as
it requires holding GPIO0 low during reset.

One really cool thing about it is the 2 MB (yes megabyte) flash, which allows using the the flash as a file system.
