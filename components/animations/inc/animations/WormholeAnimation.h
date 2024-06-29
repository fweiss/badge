#pragma once

#include "PathAnimation.h"
#include "RainbowChaser.h"

class WormholeAnimation : public PathAnimation {
public:
    WormholeAnimation();

    virtual void drawFrame(Frame &frame) override;
private:
    RainbowChaser chaser;
    void drawPath(std::vector<uint16_t>, uint32_t);

    static std::vector<std::vector<uint16_t>> paths;
};
