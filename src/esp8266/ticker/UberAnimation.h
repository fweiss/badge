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
  Animation *current;
  int index;
protected:
  unsigned int segment;
public:
  UberAnimation(unsigned long _period) {
    lastTime = 0;
    period = _period;
    index = 0;
  }
  void add(Animation *_ticker, Animation *_plasma, Animation *_square) {
    ticker = _ticker;
    plasma = _plasma;
    square = _square;
  }
  void update(unsigned long now) {
    if (now > lastTime + period) {
      lastTime = now;
      int s = index % 3;
      setCurrent(s == 1 ? square : s == 2 ? plasma : ticker );
      index++;
    }
    current->update(now);
  }
  void setCurrent(Animation *select) {
//    current->stop();
    current = select;
    current->start();
  }
};

#endif UBERANIMATION_H

