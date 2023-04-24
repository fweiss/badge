#include "WormholeAnimation.h"

const uint16_t framePeriod{100};
const uint16_t chaserLength{4};
const uint16_t chaserStep{256 * 3 / 8};

WormholeAnimation::WormholeAnimation(Display &display) : PathAnimation(display, framePeriod), chaser(chaserLength, chaserStep) {
}

// need greater chaser granularity
// default is 3 * 256 steps
// but the "roll" should be as the next color is being added to the chaser
void WormholeAnimation::drawFrame() {

    chaser.roll();

    uint16_t colorIndex = 0;
    for (std::vector<uint16_t> path :paths) {
        uint32_t color = chaser.get(colorIndex++);
        drawPath(path, color);
    }
    display.update();
}

void WormholeAnimation::drawPath(std::vector<uint16_t> path, uint32_t color) {
    for (uint16_t pixelIndex : path) {
        display.setPixel(pixelIndex, color);
    }
}

std::vector<std::vector<uint16_t>> WormholeAnimation::paths = {
        { 0, 1, 2, 3, 4, 5, 6, 7, 15, 23, 31, 39, 47, 55, 63, 62, 61, 60, 59, 58, 57, 56, 48, 40, 32, 24, 16, 8 },
        { 9, 10, 11, 12, 13, 14, 22, 30, 38, 46, 54, 53, 52, 51, 50, 49, 41, 33, 25, 17 },
        { 18, 19, 20, 21, 29, 37, 45, 44, 43, 42, 34, 26 },
        { 27, 28, 36, 35 }

};
