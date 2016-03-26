#include "FastLED.h"

#define NUM_LEDS 64
#define PIN 6

CRGB leds[NUM_LEDS];
int hue = 0;
int sat = 255;
int val = 60;

// pixel indices of various sized squares
int p1[] = { 4, 27, 28, 35, 36 };
int p2[] = { 12, 18, 19, 20, 21, 26, 29, 34, 37, 42, 43, 44, 45 };
int p3[] = { 20, 9, 10, 11, 12, 13, 14, 17, 22, 25, 30, 33, 38, 41, 46, 49, 50, 51, 52, 53, 54 };
int p4[] = { 28, 0, 1, 2, 3, 4, 5, 6, 7, 8, 15, 16, 23, 24, 31, 32, 39, 40, 47, 48, 55, 56, 57, 58, 59, 60, 61, 62, 63 };
int* pp[] = { p1, p2, p3, p4, p3, p2 };
int ppp = 1;
int vv = 90;

void setup() {
  FastLED.addLeds<WS2812, PIN>(leds, NUM_LEDS);
}

void loop() {
  for (int i=0; i<64; i++) {
    leds[i].setHSV(hue, sat, val);
  }

  int* z = pp[ppp];
  for (int i=0; i<z[0]; i++) {
    leds[z[i + 1]].setHSV(0, 0, vv);
  }
  ppp = (ppp + 1) % 6;

  FastLED.show();
  delay(100);
  hue++;
}
