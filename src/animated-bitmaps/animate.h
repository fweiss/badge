#include "FastLED.h"

class Animate {
  CRGB *leds;
  int size;
  int frame;
public:
  Animate(CRGB* leds, size_t size);
  void update();
};

