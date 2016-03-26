#include "FastLED.h"

#define NUM_LEDS 64
#define PIN 6
#define FRAME_PERIOD_MILLIS 200

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
int sss = 2;
CHSV spen(120, 255, val);

void drawBackground(CHSV hsv);
void animate(int &frameIndex, CHSV pen);
void draw(int *frame, CHSV pen);

void setup() {
  FastLED.addLeds<WS2812, PIN>(leds, NUM_LEDS);
}

void loop() {
//  drawBackground(CHSV(hue, sat, val));
  drawBackground(CHSV(0, 0, 0));
  
  animate(ppp, CHSV(0, 0, vv));
  animate(sss, spen);

  hue++;

  FastLED.show();
  delay(FRAME_PERIOD_MILLIS);
}

void drawBackground(CHSV hsv) {
  for (int i=0; i<NUM_LEDS; i++) {
    leds[i] = hsv;
  }
  
}

void animate(int &frameIndex, CHSV pen) {
  frameIndex = frameIndex % 4;
  int *frame = pp[frameIndex];
  draw(frame, pen);
  frameIndex = (frameIndex + 1) % 4;
}

void draw(int *frame, CHSV pen) {
  for (int i=0; i<frame[0]; i++) {
    leds[frame[i + 1]] = pen;
  }
  
}

