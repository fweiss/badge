#include "animate.h"

Animate::Animate(CRGB* leds, size_t size) :
  leds(leds), 
  size(size),
  pen(255, 255, 255),
  path(), 
  frame(0) {
}

void Animate::setPath(Vector<int> _path) {
  path = _path;
}

void Animate::update() {
  int hue = 0;
  int sat = 0;
  int val = 255;
  leds[frame++].setHSV(hue, sat, val);
  if (frame >= size) {
    frame = 0;
  }
}

void Animate::update2() {
  for (int i=0; i<4; i++) {
    leds[path[i]].setHSV(120, 255, 255);
  }

}

