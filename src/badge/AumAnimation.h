#ifndef AUMANIMATION_H
#define AUMANIMATION_H

#include "BitmapAnimation.h"

class AumAnimation : public BitmapAnimation {
private:
  static const byte bits[];
protected:
  void draw() override;
public:
  AumAnimation(Adafruit_NeoMatrix &matrix) : BitmapAnimation(matrix) {
    
  }  
};

const byte AumAnimation::bits[] = {
  0b10101000,
  0b01110000,
  0b01110000,
  0b00001000,
  0b00110010,
  0b00001101,
  0b10001001,
  0b01110010,  
};

void AumAnimation::draw() {
  uint32_t color = matrix.Color(20, 20, 40);
  matrix.clear();
  drawBitmap(bits, color);
  matrix.show();
}

#endif AUMANIMATION_H

