#include <Adafruit_NeoPixel.h>

static const int PIN = 6;
static const int NUMPIXELS = 64;

static int hue;

Adafruit_NeoPixel pixel = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ400);

void setup() {
  hue = 0;
  pixel.begin();
}

void loop() {
  for (int i=0; i<NUMPIXELS; i++) {
    uint32_t pen = pixel.Color(20, 30, 40);
    pixel.setPixelColor(i,  pen);
    
  }
  delay(100);

}

