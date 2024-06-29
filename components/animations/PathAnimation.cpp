#include "PathAnimation.h"

PathAnimation::PathAnimation() {

}

 void PathAnimation::drawFrame(Frame &frame) {
    for (ChaserPath cp : chaserPaths) {
        cp.chaser->roll();
        frame.drawPath(cp.path, cp.chaser);
    }
 }

// reverse the paths so that chaser gets applied reverse
void PathAnimation::reverse() {
    for (ChaserPath cp : chaserPaths) {
        cp.chaser->setReverse(false);
    }
}

// @deprecated use Frame::drawPath instead
void PathAnimation::drawPath(std::vector<uint16_t> path, Chaser *chaser) {
    // uint16_t i = 0;
    // for (int pixelIndex : path) {
    //     uint32_t pixelColor = chaser->get(i++);
    //     display.setPixel(pixelIndex, pixelColor);
    // }
}
