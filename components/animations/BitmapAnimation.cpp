#include "BitmapAnimation.h"


void BitmapAnimation::drawFrame(Frame &frame) {
    std::vector<uint32_t> currentFrame = frames.at(frameIndex);
    frame.draw(currentFrame);
    nextFrame();
}

void BitmapAnimation::drawFrame(uint16_t frameIndex) {
    // std::vector<uint32_t> frame = frames.at(frameIndex);
    // uint16_t p = 0;
    // for (uint32_t c : frame) {
    //     display.setPixel(p++, c);
    // }
    // display.update();
}

//const <std::vector<uint32_t> *frameDump() const {
//    return display.
//}
