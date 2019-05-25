#pragma once

#include <functional>

#include "BLEService.h"

class BLECharacteristicConfig {
public:
    int uuid;
};

class BLECharacteristic {
public:
    BLECharacteristic(BLEService *service, BLECharacteristicConfig config);
    virtual ~BLECharacteristic() {}

    void onWrite(std::function<void(int)> func);
};
