#pragma once

#include "animations/display.h"
#include "animations/AnimationProgram.h"

#include "blewiz/BLECharacteristic.h"

class BadgeService : public BLEService {
public:
    BadgeService(Display &display, AnimationProgram &animationProgram);
    virtual ~BadgeService();

    void init();

    void onConnect() override;
    void onDisconnect() override;

private:
    Display &display;
    AnimationProgram &animationProgram;

    BLECharacteristic batteryCharacteristic;
    BLEDescriptor batteryNotifyDesciptor;
    BLECharacteristic brightnessCharacteristic;
    BLECharacteristic programCharacteristic;

    static void batteryTask(void *parameters);
};
