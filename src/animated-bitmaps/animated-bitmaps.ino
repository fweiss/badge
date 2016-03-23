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

void mydamnfill(Bitmap m);
void mydamnfill(Bitmap m) {
  for (int i=0; i<4; i++) {
    leds[m.pixels[i]].setHSV(hue, sat, val);
  }
}

Bitmap makeit(int v, ...);
Bitmap makeit(int v, ...) {
  va_list ap;
  int i;
  va_start(ap, v);
  Bitmap *bm = (Bitmap*) malloc(sizeof(Bitmap));  
  
}

//Vector<int> meee(27, 28, 35, 36);
int z = 5;
//Vector<int> one(z);
Vector<int> box1;

void setup() {
  FastLED.addLeds<WS2812, 6>(leds, NUM_LEDS);
//  hence = makeit(27, 28, 35, 36);

  box1.push_back(1);

}

Animate awesome(leds, NUM_LEDS);

void loop() {
  for (int i=0; i<64; i++) {
    leds[i].setHSV(hue, sat, val);
  }

//  mydamnfill(thus);

  awesome.update();
  
  FastLED.show();
  delay(15);
  hue++;
}
