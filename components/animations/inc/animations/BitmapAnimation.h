#pragma once

#include "Animation.h"

#include <vector>

class BitmapAnimation : public Animation {
public:
    BitmapAnimation(Display &display);
    BitmapAnimation(Display &display, std::vector<std::vector<uint32_t>> &frames);

    static uint32_t bitmap[8][8];

protected:
    void nextFrame() { frameIndex = (frameIndex + 1) % frames.size(); }
    void drawFrame() override;

    uint16_t frameIndex;
    std::vector<std::vector<uint32_t>> &frames;

    static std::vector<std::vector<uint32_t>> zz;

};
