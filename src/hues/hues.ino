#include "FastLED.h"

#define NUM_LEDS 64

CRGB leds[NUM_LEDS];
int hue = 0;
int sat = 255;
int val = 120;

void setup() {
  FastLED.addLeds<WS2812, 6>(leds, NUM_LEDS);
}

void loop() {
  for (int i=0; i<64; i++) {
    leds[i].setHSV(hue, sat, val);
  }
  FastLED.show();
  delay(15);
  hue++;
}
