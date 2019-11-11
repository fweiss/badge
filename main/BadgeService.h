#pragma once

#include "animations/display.h"
#include "animations/AnimationProgram.h"

#include "blewiz/BLECharacteristic.h"

class BadgeService : public BLEService {
public:
    BadgeService(Display &display, AnimationProgram &animationProgram);
    virtual ~BadgeService();

    void init();

private:
    Display &display;
    AnimationProgram &animationProgram;

    BLECharacteristic batteryCharacteristic;
    BLECharacteristic brightnessCharacteristic;
    BLECharacteristic programCharacteristic;

    static void batteryTask(void *parameters);
};
