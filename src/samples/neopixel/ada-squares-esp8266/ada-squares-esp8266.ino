#include <Adafruit_NeoPixel.h>

#define PIN 5
#define NUMPIXELS 64
#define DELAY 500

#define CHSV uint32_t

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

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

CHSV red = pixels.Color(60, 0, 0);
CHSV orange = pixels.Color(40, 20, 0);
CHSV green = pixels.Color(0, 60, 0);
CHSV blue = pixels.Color(0, 0, 60);

Animation box1 = { 4, 0, pp, red };
Animation box2 = { 4, 1, pp, orange };
Animation box3 = { 4, 2, pp, green };
Animation box4 = { 4, 3, pp, blue }; 

void setup() {
  pixels.begin(); 
}

void loop() {
//  for (int i=0; i<NUMPIXELS; i++) {
//    pixels.setPixelColor(i, pixels.Color(0, 150, 0));
//  }

  box1.animate();
  box2.animate();
  box3.animate();
  box4.animate();
 
  pixels.show();
  delay(DELAY);
}

void draw(int *frame, CHSV pen) {
  for (int i=0; i<frame[0]; i++) {
    pixels.setPixelColor(frame[i + 1],  pen);
  }
 
}
