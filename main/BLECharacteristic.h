#pragma once

#include <functional>

#include "BLEService.h"

class BLECharacteristicConfig {
public:
    const esp_bt_uuid_t uuid;
    const esp_gatt_perm_t permissions;
    const esp_gatt_char_prop_t properties;
    esp_attr_control_t control;
};

class BLECharacteristic {
public:
    BLECharacteristic(BLEService *service, BLECharacteristicConfig &config);
    virtual ~BLECharacteristic() {}

    void setWriteCallback(std::function<void(int)> func);
    void setReadCallback(std::function<void(int)> func);

    std::function<void(int)> writeCallback;
    std::function<void(int)> readCallback;

    const esp_gatt_perm_t &permissions;
    const esp_gatt_char_prop_t &properties;
    esp_attr_control_t &control; // fixme not const to comply with API

protected:
    void onRead();
    void onWrite();

private:
};
