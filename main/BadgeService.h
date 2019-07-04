#pragma once

#include "animations/display.h"
#include "animations/AnimationProgram.h"

#include "BLECharacteristic.h"


class BadgeService : public BLEService {
public:
    BadgeService(Display &display, AnimationProgram &animationProgram);
    virtual ~BadgeService() {}

    void init();

private:
    Display &display;
    AnimationProgram animationProgram;

    BLECharacteristic brightnessCharacteristic;
    BLECharacteristic programCharacteristic;
};
