#ifndef FACEANIMATION_H
#define FACEANIMATION_H

#include "BitmapAnimation.h"

class FaceAnimation : public BitmapAnimation {
private:
  uint32_t faceColor;
  static const byte face[];
  static const byte eyes[];
protected:
  void draw() override;
public:
  FaceAnimation(Adafruit_NeoMatrix &matrix) : BitmapAnimation(matrix) {
    faceColor = matrix.Color(71, 41, 30);      
  }
};

const byte FaceAnimation::face[] = {
  0b00011000, 
  0b01111110, 
  0b01111110, 
  0b11111111, 
  0b11111111, 
  0b01111110, 
  0b01111110, 
  0b00011000
};
const byte FaceAnimation::eyes[] {
  0b00000000,
  0b00000000,
  0b00000000,
  0b00100100,
  0b00000000,
  0b00000000,
  0b00000000,
  0b00000000,  
};

void FaceAnimation::draw() {
  matrix.fillScreen(0);
  uint32_t eyeColor = matrix.Color(0, 0, 40);
  uint32_t mouthColor = matrix.Color(40, 0, 0);
  // actually x, y
  drawBitmap(face, faceColor);
  if (frame % 25 != 0) {
    matrix.drawPixel(2, 3, eyeColor);
    matrix.drawPixel(5, 3, eyeColor);
  }
  matrix.drawPixel(3, 6, mouthColor);
  matrix.drawPixel(4, 6, mouthColor);
  matrix.show();
  frame++;
}

#endif FACEANIMATION_H

