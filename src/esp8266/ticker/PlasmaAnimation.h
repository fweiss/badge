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
  Point lissajous(float a, float b, float c) {
    float x = sin(phase * a);
    float y = sin(phase * b);
    // scale to fit in matrix
    Point point = { (x + 1.0) * rows / 2, (y + 1.0) * cols / 2 };
    return point;
  }
  float distance(Point a, Point b) {
    Point d = { a.x - b.x, a.y - b.y };
    return sqrt(d.x * d.x + d.y * d.y);
  }
};

void PlasmaAnimation::draw() {

  // this makes a nice "bug" that wanders across the screen, mostly at the edges, like
  // it's trying to escape, pausing every so often, especially in the corners
  Point p1 = lissajous(1, 1.2, 0);
  Point p2 = lissajous(3, 4.2, 0);
  Point p3 = lissajous(5, 3.2, 0);
  matrix.fillScreen(0);
//  matrix.drawPixel(p1.x, p1.y, matrix.Color(20, 50, 40));
  phase += 0.2; //0.02;

  
  byte row;
  byte col;
  for (row = 0; row < rows; row++) {
    for (col = 0; col < cols; col++) {
      Point rc = { row, col };
      // max = ~ 12
      float d1 = distance(p1, rc);
      float d2 = distance(p2, rc);
      float d3 = distance(p3, rc);
      float r = 150.0 - (d1 + d2) * 8;
      float g = 150.0 - (d2 + d3) * 8;
      float b = 150.0 - (d3 + d1) * 8;
      uint32_t color = matrix.Color(r/2, g/2, b/2);
      matrix.drawPixel(row, col, color);
    }
  }
  
}

#endif PLASMAANIMATION_H

