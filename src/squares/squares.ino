#include "FastLED.h"

#define NUM_LEDS 64
#define PIN 6
#define FRAME_PERIOD_MILLIS 200

CRGB leds[NUM_LEDS];
int hue = 0;
int sat = 255;
int val = 60;
int vv = 90;

// pixel indices of various sized squares
int p1[] = { 4, 27, 28, 35, 36 };
int p2[] = { 12, 18, 19, 20, 21, 26, 29, 34, 37, 42, 43, 44, 45 };
int p3[] = { 20, 9, 10, 11, 12, 13, 14, 17, 22, 25, 30, 33, 38, 41, 46, 49, 50, 51, 52, 53, 54 };
int p4[] = { 28, 0, 1, 2, 3, 4, 5, 6, 7, 8, 15, 16, 23, 24, 31, 32, 39, 40, 47, 48, 55, 56, 57, 58, 59, 60, 61, 62, 63 };
int* pp[] = { p1, p2, p3, p4, p3, p2 };

void drawBackground(CHSV hsv);
void draw(int *frame, CHSV pen);

class Animation {
public:
  int frameCount;
  int frameIndex;
  int **frames;
  CHSV pen;
  void animate() {
    frameIndex = frameIndex % frameCount;
    int *frame = frames[frameIndex];
    draw(frame, pen);
    frameIndex = (frameIndex + 1) % frameCount;
  }
};

CHSV white(0, 0, val);
CHSV black(0, 0, 0);
CHSV red(0, 255, val);
CHSV orange(80, 255, val);
CHSV yellow(64, 255, val);
CHSV green(96, 255, val);
CHSV blue(160, 255, val);
CHSV violet(192, 255, val);
CHSV pink(224, 255, val);

//Animation box1 = { 4, 0, pp, CHSV(27, 255, val) };
//Animation box2 = { 4, 1, pp, CHSV(170, 255, val) };
//Animation box3 = { 4, 2, pp, CHSV(0, 0, vv /2) };
//Animation box4 = { 4, 3, pp, CHSV(120, 255, val) }; 
Animation box1 = { 4, 0, pp, red };
Animation box2 = { 4, 1, pp, orange };
Animation box3 = { 4, 2, pp, green };
Animation box4 = { 4, 3, pp, blue }; 

void setup() {
  FastLED.addLeds<WS2812, PIN>(leds, NUM_LEDS);
}

void loop() {
//  drawBackground(CHSV(hue, sat, val));
  drawBackground(CHSV(0, 0, 0));
  
  box1.animate();
  box2.animate();
  box3.animate();
  box4.animate();

  hue++;

  FastLED.show();
  delay(FRAME_PERIOD_MILLIS);
}

void drawBackground(CHSV hsv) {
  for (int i=0; i<NUM_LEDS; i++) {
    leds[i] = hsv;
  }
  
}

void draw(int *frame, CHSV pen) {
  for (int i=0; i<frame[0]; i++) {
    leds[frame[i + 1]] = pen;
  }
  
}

