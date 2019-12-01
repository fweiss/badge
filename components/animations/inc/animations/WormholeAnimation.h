#pragma once

#include "PathAnimation.h"
#include "RainbowChaser.h"

class WormholeAnimation : public PathAnimation {
public:
    WormholeAnimation(Display &display);

    virtual void drawFrame() override;
private:
    RainbowChaser chaser;
    void drawPath(std::vector<uint16_t>, uint32_t);

    static std::vector<std::vector<uint16_t>> paths;
};
