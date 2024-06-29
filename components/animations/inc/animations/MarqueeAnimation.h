#pragma once

#include "PathAnimation.h"
#include "RainbowChaser.h"

class MarqueeAnimation : public PathAnimation {
public:
    MarqueeAnimation();

    // void drawFrame();
    virtual void drawFrame(Frame &frame) override;
protected:
    RainbowChaser chaser;
    static std::vector<std::vector<uint16_t>> paths;
};
