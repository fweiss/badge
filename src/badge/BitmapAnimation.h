#ifndef BITMAPANIMATION_H
#define BITMAPANIMATION_H

#include "Animation.h"

class BitmapAnimation : public Animation {
private:
  uint32_t color;
  static const byte bits[];
  static const byte eyes[];
  uint32_t frame;
protected:
  void draw() override;
  boolean isSet(int x, int y) {
    byte b = bits[y];
    return b & (1 << (7 - x));
  }
public:
  BitmapAnimation(Adafruit_NeoMatrix &matrix) : Animation(matrix) {
    color = matrix.Color(71, 41, 30);
    frame = 0;
  }
};

const byte BitmapAnimation::bits[] = {
  0b00011000, 
  0b01111110, 
  0b01111110, 
  0b11111111, 
  0b11111111, 
  0b01111110, 
  0b01111110, 
  0b00011000
};
const byte BitmapAnimation::eyes[] {
  0b00000000,
  0b00000000,
  0b00000000,
  0b00100100,
  0b00000000,
  0b00000000,
  0b00000000,
  0b00000000,  
};

void BitmapAnimation::draw() {
  matrix.fillScreen(0);
  uint32_t eyeColor = matrix.Color(0, 0, 40);
  uint32_t mouthColor = matrix.Color(40, 0, 0);
  // actually x, y
  for (int row=0; row<8; row++) {
    for (int col=0; col<8; col++) {
      if (isSet(row, col)) {
        matrix.drawPixel(row, col, color);
      }
    }
  }
  if (frame % 25 != 0) {
    matrix.drawPixel(2, 3, eyeColor);
    matrix.drawPixel(5, 3, eyeColor);
  }
  matrix.drawPixel(3, 6, mouthColor);
  matrix.drawPixel(4, 6, mouthColor);
  matrix.show();
  frame++;
}

#endif BITMAPANIMATION_H
