#pragma once

#include "Animation.h"

class Plasma : public Animation {
public:
    Plasma();
    virtual ~Plasma() {}

    void drawFrame(Frame &frame) override;
    float phase;
};
