#include "Frame.h"

void Frame::drawPath(std::vector<uint16_t> path, Chaser *chaser) {
    uint16_t i = 0;
    for (int pixelIndex : path) {
        uint32_t pixelColor = chaser->get(i++);
        setPixel(pixelIndex, pixelColor);
    }
}

void Frame::draw(std::vector<uint32_t> frame) {
    uint16_t p = 0;
    for (uint32_t c : frame) {
        setPixel(p++, c);
    }
}

void Frame::drawPath(std::vector<uint16_t> path, uint32_t color) {
    for (uint16_t pixelIndex : path) {
        setPixel(pixelIndex, color);
    }
}
