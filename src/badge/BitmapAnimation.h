#ifndef BITMAPANIMATION_H
#define BITMAPANIMATION_H

#include "Animation.h"

class BitmapAnimation : public Animation {
private:
protected:
  uint32_t frame;
  virtual void draw() = 0;
  boolean isSet(const byte* bits, int x, int y) {
    byte b = bits[y];
    return b & (1 << (7 - x));
  }
  void drawBitmap(const byte* bits, uint32_t color) {
    for (int row=0; row<8; row++) {
      for (int col=0; col<8; col++) {
        if (isSet(bits, row, col)) {
          matrix.drawPixel(row, col, color);
        }
      }
    }
  }
public:
  BitmapAnimation(Adafruit_NeoMatrix &matrix) : Animation(matrix) {
    frame = 0;
  }
};

#endif BITMAPANIMATION_H
