#pragma once

#include <functional>

class BLECharacteristicConfig {
public:
    int uuid;
};

class BLECharacteristic {
public:
    BLECharacteristic(BLECharacteristicConfig config);
    virtual ~BLECharacteristic() {}

    void onWrite(std::function<void(int)> func);
};
