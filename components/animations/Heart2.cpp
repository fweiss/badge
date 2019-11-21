#include "Heart2.h"

Heart2::Heart2(Display &display) : BitmapAnimation(display, heart) {

}

void Heart2::drawFrame() {
    drawFrame(frameIndex);
    nextFrame();
}

void Heart2::drawFrame(uint16_t frameIndex) {
    std::vector<uint32_t> frame = frames.at(frameIndex);
    uint16_t p = 0;
    for (uint32_t c : frame) {
        display.setPixel(p++, c);
    }
    display.update();
}

#define purple 0x640000

std::vector<std::vector<uint32_t>> Heart2::heart = {
    {
        0, purple, purple, 0, 0 , purple, purple, 0,
        purple, purple, purple, purple, purple, purple, purple, purple,
        purple, purple, purple, purple, purple, purple, purple, purple,
        purple, purple, purple, purple, purple, purple, purple, purple,
        purple, purple, purple, purple, purple, purple, purple, purple,
        0, purple, purple, purple, purple, purple, purple, 0,
        0, 0, purple, purple, purple, purple, 0, 0,
        0, 0, 0, purple, purple, 0, 0, 0,
    },
    {
        0, 0, 0, 0, 0 , 0, 0, 0,
        0, purple, purple, 0, 0, purple, purple, 0,
        0, purple, purple, purple, purple, purple, purple, 0,
        0, purple, purple, purple, purple, purple, purple, 0,
        0, purple, purple, purple, purple, purple, purple, 0,
        0, 0, purple, purple, purple, purple, 0, 0,
        0, 0, 0, purple, purple, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
    },
};
