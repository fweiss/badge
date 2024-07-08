#include "BitmapAnimation.h"


void BitmapAnimation::drawFrame(Frame &frame) {
    std::vector<uint32_t> currentFrame = frames.at(frameIndex);
    frame.draw(currentFrame);
    nextFrame();
}
