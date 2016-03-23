#include "animate.h"

Animate::Animate(CRGB* leds, size_t size) : leds(leds), size(size), frame(0) {}

void Animate::update() {
  int hue = 0;
  int sat = 0;
  int val = 255;
  leds[frame++].setHSV(hue, sat, val);
  if (frame >= size) {
    frame = 0;
  }
}

