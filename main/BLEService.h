#pragma once

#include <map>

#include "freertos/FreeRTOS.h"

#include "esp_gatts_api.h"

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
    void onCharacteristicWrite(struct esp_ble_gatts_cb_param_t::gatts_write_evt_param);

    static const uint16_t ATTR_MAX_LEN = 16;

protected:
    std::map<int, BLECharacteristic*> characteristics;

private:
    uint16_t serviceHandle;
    void onCharacteristicWrite();
    void onCharacteristicRead();
};
