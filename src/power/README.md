# Power

This is a simple sketch that runs all 64 LEDs statically (no animation) to allow measuring electrical power consumption,
heat dissipation, and luminous output. Change the ``val`` variable to test different RGB levels.

## Observations

The actual current draw of each LED at maximum brightness at 5 V is 11 mA, much less than the published rating
of 20 mA.

For battery consumption, the controller current draw should also be taken into consideration. This varies by the
type of controller used. The Arduino Pro Mini, running at 5 V, consumed about 16 mA.

## Conclusions

The heat dissipation is the primary limitation for use as a wearable.
Above about 500 mW, the heat dissipation becomes noticable and above 2 W
there would be discomfort when worn against the body or in clothing. At maximum
brightness, the 64 LEDs dissipate over 10 W, making the array very hot to the touch.

Consequently, it's recommended to not use the unit as a wearable at more than 400 mA, which corresponds
to an RGB of 41.

## Test results

Fluke 115
Triad AWSP-40-5
Arduino Pro Mini

| RGB | I (mA) | P (mW) | Brightness              | Heat     |
|----:|-------:|-------:|-------------------------|----------|
|   0 | 57     | 285    | none                    | none     |
|   1 | 57     | 285    | none                    | none     |
|   2 | 59     | 295    | very dim, distinct leds | none     |
|   3 | 62     | 310    | very dim, distinct leds |          |
|   7 | 75     | 375    | low                     | tepid    |
|  15 | 117    | 585    | medium                  | tepid    |
|  31 | 268    | 1340   | medium                  | tepid    |
|  41 | 399    | 2000   | bright                  | warm     |
|  49 | 495    | 2475   | bright                  | warm     |
|  63 | 665    | 3325   | very bright             | medium   |
| 127 | 1285   | 6425   | very, very bright       | hot      |
| 255 | 2151   | 10775  | extremely bright        | very hot |
