#ifndef PLASMAANIMATION_H
#define PLASMAANIMATION_H

#include "Animation.h"

struct Point {
  float x;
  float y;
};

class PlasmaAnimation : public Animation {
private:
protected:
  void draw() override;
  float phase;
public: 
  const byte rows = 8;
  const byte cols = 8;
  PlasmaAnimation(Adafruit_NeoMatrix &matrix) : Animation(matrix) {
  }
  Point lissajou(float a, float b, float c) {
    float x = sin(phase * a);
    float y = sin(phase * b);
    // scale to fit in matrix
    Point point = { (x + 1.0) * rows / 2, (y + 1.0) * cols / 2 };
    return point;
  }
};

void PlasmaAnimation::draw() {

  // this makes a nice "bug" that wanders across the screen, mostly at the edges, like
  // it's trying to escape, pausing every so often, especially in the corners
  Point p = lissajou(1, 1.2, 0);
  matrix.fillScreen(0);
  matrix.drawPixel(p.x, p.y, matrix.Color(20, 50, 40));
  phase += 0.2; //0.02;

  
  byte row;
  byte col;
  for (row = 0; row < rows; row++) {
    for (col = 0; col < cols; col++) {
      float r;
      float g;
      float b;
      uint32_t color = matrix.Color(r, g, b);
//      matrix.drawPixel(row, col, color);
    }
  }
  
}

#endif PLASMAANIMATION_H

