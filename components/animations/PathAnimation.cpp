#include "PathAnimation.h"

PathAnimation::PathAnimation(Display &display) : Animation(display) {

}

PathAnimation::PathAnimation(Display &display, uint16_t framePeriodMilis) : Animation(display, framePeriodMilis){

}

void PathAnimation::drawFrame() {
    for (ChaserPath cp : chaserPaths) {
        cp.chaser->roll();
        drawPath(cp.path, cp.chaser);
    }
    display.show();
}

// reverse the paths so that chaser gets applied reverse
void PathAnimation::reverse() {
    for (ChaserPath cp : chaserPaths) {
        cp.chaser->setReverse(false);
    }
}

void PathAnimation::drawPath(std::vector<uint16_t> path, Chaser *chaser) {
    uint16_t i = 0;
    for (int pixelIndex : path) {
        uint32_t pixelColor = chaser->get(i++);
        display.setPixel(pixelIndex, pixelColor);
    }
}
