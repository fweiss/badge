#pragma once

#include "Animation.h"
#include "Display.h"

class SmearAnimation : public Animation {
private:
    uint16_t r;
protected:
public:
    SmearAnimation(Display &display);
    void drawFrame() override;
};
