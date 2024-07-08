#pragma once

#include "Animation.h"

#include <vector>

class BitmapAnimation : public Animation {
public:
    BitmapAnimation();
    BitmapAnimation(std::vector<std::vector<uint32_t>> &frames): frames(frames), frameIndex(0) {};
    BitmapAnimation(std::vector<std::vector<uint32_t>> &frames, uint16_t period): frames(frames), frameIndex(0) {
        this->framePeriodMillis = period;
    };

    typedef std::vector<std::vector<uint32_t>> Frames;

protected:
    virtual void nextFrame() { frameIndex = (frameIndex + 1) % frames.size(); }
    virtual void drawFrame(Frame &frame);

    std::vector<std::vector<uint32_t>> &frames;
    uint16_t frameIndex;
};
