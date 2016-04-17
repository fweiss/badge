#ifndef ANIMATION_H
#define ANIMATION_H

#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>

class Animation {
private:
  unsigned long lastTime;
  unsigned long period;
protected:
  Adafruit_NeoMatrix &matrix;
  virtual void draw() {
  }
public:
  Animation(Adafruit_NeoMatrix &matrix);
  void update(unsigned long now) {
    if (now >= lastTime + period) {
      lastTime = now;
      draw();
    }
  }
};

Animation::Animation(Adafruit_NeoMatrix &m) : matrix(m) {
  lastTime = 0;
  period = 100;
}

#endif ANIMATION_H


