#pragma once

#include <functional>

class BLECharacteristicConfig {

};

class BLECharacteristic {
public:
    BLECharacteristic(BLECharacteristicConfig config);
    virtual ~BLECharacteristic() {}

    void onWrite(std::function<void(int)> func);
};
