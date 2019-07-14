#pragma once

#include "Animation.h"
#include "display.h"

class Animation {
private:
protected:
    Display &display;
public:
    Animation(Display &display);
    virtual ~Animation() {};
    virtual void drawFrame() = 0;
};
