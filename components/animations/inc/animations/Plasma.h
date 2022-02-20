#pragma once

#include "Animation.h"
#include "Display.h"

class Plasma : public Animation {
public:
    Plasma(Display &display);
    virtual ~Plasma() {}

    void drawFrame() override;
    float phase;
};
