#ifndef UBER_ANIMATION_H
#define UBER_ANIMATION_H

#include "Animation.h"

class UberAnimation {
private:
    unsigned long lastTime;
    unsigned long period;
    bool running = false;
    int index;
    Animation *current;
protected:
    static Animation *animations[];
    int animationsSize;
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
    void setup() {
    }
    void update(unsigned long now) {
        //  also quit if current has been stopped
        if (lastTime == 0 || now > lastTime + period || ! current->isRunning()) {
            lastTime = now;

            int nextIndex = findNextRunningIndex();
            if (nextIndex > -1) {
                setCurrent(animations[nextIndex]);
                index = nextIndex;
            }
        }
        current->update(now);
    }
    void setCurrent(Animation *select) {
        current = select;
        current->start();
    }
    int findNextRunningIndex() {
        int s = (index + 1) % animationsSize;
        for (int i=0; i<animationsSize; i++) {
            int candIndex = (s + i) % animationsSize;
                Animation* cand = animations[candIndex];
//                if (cand->isRunning()) {
                if (cand->isEnabled()) {
                return candIndex;
            }
        }
        return -1;
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

#endif UBER_ANIMATION_H

