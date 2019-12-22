#pragma once

#include "PathAnimation.h"
#include "RainbowChaser.h"

class MarqueeAnimation : public PathAnimation {
public:
    MarqueeAnimation(Display &display);

    void drawFrame();
protected:
    RainbowChaser chaser;
    static std::vector<std::vector<uint16_t>> paths;
};
