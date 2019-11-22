#include "BitmapAnimation.h"

//BitmapAnimation::BitmapAnimation(Display &display) : BitmapAnimation(display, zz) {
//
//}

BitmapAnimation::BitmapAnimation(Display &display, std::vector<std::vector<uint32_t>> &frames) :
    Animation(display), frameIndex(0), frames(frames) {

}

void BitmapAnimation::drawFrame() {
    drawFrame(frameIndex);
    nextFrame();
}

void BitmapAnimation::drawFrame(uint16_t frameIndex) {
    std::vector<uint32_t> frame = frames.at(frameIndex);
    uint16_t p = 0;
    for (uint32_t c : frame) {
        display.setPixel(p++, c);
    }
    display.update();
}
