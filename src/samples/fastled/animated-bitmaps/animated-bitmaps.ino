#include "vector.h"
#include "animate.h"
#include "FastLED.h"

#define NUM_LEDS 64

CRGB leds[NUM_LEDS];
int hue = 0;
int sat = 255;
int val = 60;


typedef struct Bitmap {
  int states;
  int pixels[4];
} Bitmap;

Bitmap thus = { 4, { 27, 28, 35, 36 } };
Bitmap hence;

Bitmap makeit(int v, ...);
Bitmap makeit(int v, ...) {
  va_list ap;
  int i;
  va_start(ap, v);
  Bitmap *bm = (Bitmap*) malloc(sizeof(Bitmap));  
  
}

Animate awesome(leds, NUM_LEDS);
Animate box2(leds, NUM_LEDS);
Vector<int> path(27, 28, 35, 36);

void setup() {
  FastLED.addLeds<WS2812, 6>(leds, NUM_LEDS);
  box2.setPath(path);
}


void loop() {
  for (int i=0; i<64; i++) {
    leds[i].setHSV(hue, sat, val);
  }
  awesome.update();
  box2.update2();
  FastLED.show();
  delay(15);
  hue++;
}
