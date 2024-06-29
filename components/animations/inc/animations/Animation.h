#pragma once

#include "Frame.h"

class Animation {
public:
    Animation();
    Animation(uint16_t framePeriodMillis): framePeriodMillis(framePeriodMillis) {};
    virtual ~Animation() {};

    virtual void drawFrame(Frame &frame) = 0;

    virtual const std::vector<uint32_t> *frameDump() const;
    uint16_t getFramePeriodMillis() { return this->framePeriodMillis; }
protected:
    uint16_t framePeriodMillis;
    uint32_t frameIndex = 0;
};
