#ifndef ANIMATION_SEQUENCE_H
#define ANIMATION_SEQUENCE_H

#include "Animation.h"

extern TickerAnimation ticker;
extern StackAnimation stack;
extern PlasmaAnimation plasma;
extern PixelAnimation pixel;
extern FaceAnimation face;
extern AumAnimation sacred;
extern SpiralAnimation spiral;
extern WormholeAnimation wormhole;

class AnimationSequence {
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
    AnimationSequence(unsigned long _period) {
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
    	for (int i=0; i<animationsSize; i++) {
            Animation* animation = animations[i];
    		animation->enable(false);
    	}
    	setCurrent(&wormhole);
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

Animation* AnimationSequence::animations[] {
    &ticker, &stack, &plasma, &pixel, &face, &sacred, &spiral, &wormhole, NULL
};

#endif ANIMATION_SEQUENCE_H
