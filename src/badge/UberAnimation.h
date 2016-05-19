#ifndef UBERANIMATION_H
#define UBERANIMATION_H

#include "Animation.h"

class UberAnimation {
private:
  unsigned long lastTime;
  unsigned long period;
  bool running = false;
  Animation *__ticker;
  Animation *mplasma;
  Animation *square;
  Animation *current;
  int index;
  static Animation *animations[];
  int animationsSize;
protected:
  unsigned int segment;
public:
  UberAnimation(unsigned long _period) {
    lastTime = 0;
    period = _period;
    index = 0;
    for (int i=0; i<100; i++) {
      if (animations[i] == 0) {
        animationsSize = i;
        break;
      }
    }
  }
  void add(Animation *_ticker, Animation *_plasma, Animation *_square) {
    __ticker = _ticker;
    mplasma = _plasma;
    square = _square;
  }
  Animation* getByIndex(int s) {
//    return s == 1 ? square : s == 2 ? mplasma : __ticker;
    return animations[s]; 
  }
  void update(unsigned long now) {
    if (lastTime == 0 || now > lastTime + period) {
      lastTime = now;
      
      int s = (index + 1) % animationsSize;
      for (int i=0; i<animationsSize; i++) {
        int candIndex = (s + i) % animationsSize;
        Animation* cand = getByIndex(candIndex);
        if (cand->isRunning()) {
          setCurrent(cand);
          index = candIndex;
          break;
        }
      }
    }
    current->update(now);
  }
  void setCurrent(Animation *select) {
//    current->stop();
    current = select;
    current->start();
  }
};

extern TickerAnimation ticker;
extern StackAnimation stack;
extern PlasmaAnimation plasma;
extern PixelAnimation pixel;
extern FaceAnimation face;
extern AumAnimation sacred;

Animation* UberAnimation::animations[] {
  &ticker, &stack, &plasma, &pixel, &face, &sacred, NULL
};

#endif UBERANIMATION_H

