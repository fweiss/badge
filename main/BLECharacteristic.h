#pragma once

#include <functional>

#include "BLEService.h"

class BLECharacteristicConfig {
public:
    int uuid;
};

class BLECharacteristic {
public:
    BLECharacteristic(BLEService *service, BLECharacteristicConfig &config);
    virtual ~BLECharacteristic() {}

    void setWriteCallback(std::function<void(int)> func);
    void setReadCallback(std::function<void(int)> func);

    std::function<void(int)> writeCallback;
    std::function<void(int)> readCallback;

protected:
    void onRead();
    void onWrite();

private:
};
