#pragma once

#include "Animation.h"
#include "Display.h"
#include "motion/Motion.hpp"

class Gravity : public Animation {
public:
    Gravity(Display &display);
    virtual ~Gravity() {}

    void drawFrame() override;

    void setMotion(MotionData motionData);
private:
    MotionData motionData;

    uint8_t x,y;
};
