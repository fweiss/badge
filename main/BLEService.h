#pragma once

#include "freertos/FreeRTOS.h"

class BLEService {
public:
    BLEService() {}
    virtual ~BLEService() {}

    void registerCharacteristic();

    static const uint16_t ATTR_MAX_LEN = 16;
private:
    uint16_t serviceHandle;
};
