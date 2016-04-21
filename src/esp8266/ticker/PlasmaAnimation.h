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
  // map -1 .. +1 to 0 .. +s
  Point lissajous(float a, float b, float c) {
    const float scale = 1.2;
    float x = sin(phase * a) * scale;
    float y = sin(phase * b) * scale;
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

  Point p1 = lissajous(1, 1.2, 0);
  Point p2 = lissajous(3, 4.2, 0);
  Point p3 = lissajous(5, 3.2, 0);
  matrix.fillScreen(0);
  phase += 0.2; //0.02;

  // this makes a nice "bug" that wanders across the screen, mostly at the edges, like
  // it's trying to escape, pausing every so often, especially in the corners
//  matrix.drawPixel(p2.x, p1.y, matrix.Color(20, 50, 40));

  
  byte row;
  byte col;
  for (row = 0; row < rows; row++) {
    for (col = 0; col < cols; col++) {
      Point rc = { row, col };
      // max = ~ 12
      float d1 = distance(p1, rc);
      float d2 = distance(p2, rc);
      float d3 = distance(p3, rc);
      const float scale = 60.0;
      const float base = 20.0;
      float r = (sin(d1 * d2 * 0.1) + 1.0) * scale + base;
      float g = (sin(d2 * d3 * 0.1) + 1.0) * scale + base;
      float b = (sin(d3 * d1 * 0.1) + 1.0) * scale + base;

      // make the dominant color more dominant
      
      
      if (r < 0) r = 0; if (r > 511) r = 511;
      if (g < 0) r = 0; if (g > 511) g = 511;
      if (b < 0) b = 0; if (b > 511) b = 511;
      uint32_t color = matrix.Color(r/2, g/2, b/2);
      matrix.drawPixel(row, col, color);
    }
  }
  
}

#endif PLASMAANIMATION_H

