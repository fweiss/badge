#pragma once

#include <vector>

#include "Display.h"

class Animation {
public:
    Animation(Display &display);
    Animation(Display &display, uint16_t framePeriodMilis);
    virtual ~Animation() {};

    virtual void drawFrame() = 0;
    virtual const std::vector<uint32_t> *frameDump() const;
    uint16_t getFramePeriodMillis() { return this->framePeriodMillis; }
protected:
    Display &display;
    uint16_t framePeriodMillis;
    uint32_t frameIndex = 0;

    // int matrix = 0;
    // int lastTime = 0;
    // int period = 0;
};
