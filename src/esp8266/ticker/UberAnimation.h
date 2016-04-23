#ifndef UBERANIMATION_H
#define UBERANIMATION_H

#include "Animation.h"

class UberAnimation {
private:
  unsigned long lastTime;
  unsigned long period;
  bool running = false;
  Animation *ticker;
  Animation *plasma;
  Animation *square;
protected:
  unsigned int segment;
public:
  UberAnimation(unsigned long _period) {
    period = _period;
  }
  void add(Animation *_ticker, Animation *_plasma, Animation *_square) {
    ticker = _ticker;
    plasma = _plasma;
    square = _square;
  }
};

#endif UBERANIMATION_H

