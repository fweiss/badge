#ifndef ANIMATION_H
#define ANIMATION_H

#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>

class Animation {
private:
  unsigned long lastTime;
  unsigned long period;
  bool running = false;
protected:
  Adafruit_NeoMatrix &matrix;
  virtual void draw() {
  }
public:
  Animation(Adafruit_NeoMatrix &matrix);
  void start() {
    running = true;
  }
  void stop() {
    running = false;
  }
  void update(unsigned long now) {
    if (running && now >= lastTime + period) {
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


