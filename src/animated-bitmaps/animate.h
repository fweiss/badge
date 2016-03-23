#include "FastLED.h"
#include "vector.h"

class Animate {
  CRGB *leds;
  int size;
  CRGB pen;
  Vector<int> path;
  int frame;
public:
  Animate(CRGB* leds, size_t size);
  void setPath(Vector<int> path);
  void update();
  void update2();
};

