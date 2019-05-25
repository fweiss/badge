#pragma once

#include <map>

#include "freertos/FreeRTOS.h"

//#include "BLECharacteristic.h"
class BLECharacteristic;
class BLECharacteristicConfig;

class BLEService {
public:
    BLEService();
    virtual ~BLEService() {}

    // todo make friend
    void attach(BLECharacteristic *characteristic, BLECharacteristicConfig &config);

    void onCharacteristicRead(int uuid);
    void onCharacteristicWrite(int uiid);

    static const uint16_t ATTR_MAX_LEN = 16;

protected:
    std::map<int, BLECharacteristic*> characteristics;

private:
    uint16_t serviceHandle;
    void onCharacteristicWrite();
    void onCharacteristicRead();
};
