#ifndef UBERANIMATION_H
#define UBERANIMATION_H

#include "Animation.h"

class UberAnimation : public Animation {
private:
  Animation *tickerAnimation;
  Animation *plasmaAnimation;
  
protected:
public:
  UberAnimation(Adafruit_NeoMatrix &matrix) : Animation(matrix) {
    
  }
};

#endif UBERANIMATION_H

