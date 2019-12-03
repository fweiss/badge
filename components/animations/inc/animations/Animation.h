#pragma once

#include "Display.h"

class Animation {
public:
    Animation(Display &display);
    Animation(Display &display, uint16_t framePeriodMilis);

    virtual ~Animation() {};
    virtual void drawFrame() = 0;
    uint16_t getFramePeriodMillis() { return this->framePeriodMillis; }
protected:
    Display &display;
    uint16_t framePeriodMillis;
};
