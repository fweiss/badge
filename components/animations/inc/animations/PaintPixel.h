#pragma once

#include "BitmapAnimation.h"

typedef uint32_t Color;

class PaintPixel : public BitmapAnimation {
public:
    PaintPixel(Display &display);

    void setPixelColor(uint16_t x, uint16_t y, Color color);
private:
    static std::vector<std::vector<uint32_t>> frames;
};
