#pragma once

#include "BLECharacteristic.h"

class BadgeService {
public:
    BadgeService();
    virtual ~BadgeService() {}

    void init();

private:
    int display;

    BLECharacteristic dimmingCharacteristic;
};
