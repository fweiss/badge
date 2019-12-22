#pragma once

#include "Animation.h"

#include <vector>

class BitmapAnimation : public Animation {
public:
    typedef std::vector<std::vector<uint32_t>> Frames;

    BitmapAnimation(Display &display);
    BitmapAnimation(Display &display, std::vector<std::vector<uint32_t>> &frames);
    BitmapAnimation(Display &display, std::vector<std::vector<uint32_t>> &frames, uint16_t framePeriodMilis);

protected:
    void nextFrame() { frameIndex = (frameIndex + 1) % frames.size(); }
    void drawFrame() override;
    void drawFrame(uint16_t frameIndex);

    uint16_t frameIndex;
    std::vector<std::vector<uint32_t>> &frames;
};
