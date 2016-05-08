#include "FastLED.h"

#define NUM_LEDS 64
#define PIN 6

CRGB leds[NUM_LEDS];
int val = 41;

void setup() {
  FastLED.addLeds<WS2812, PIN>(leds, NUM_LEDS);
  for (int i=0; i<64; i++) {
    leds[i].setRGB(val, val, val);
    FastLED.show();
  }
}

void loop() {
}
