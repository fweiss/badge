#pragma once

#include "animations/display.h"

#include "BLECharacteristic.h"


class BadgeService : public BLEService {
public:
    BadgeService(Display &display);
    virtual ~BadgeService() {}

    void init();

private:
    Display &display;

    BLECharacteristic brightnessCharacteristic;
    BLECharacteristic programCharacteristic;
};
