#pragma once

#include <functional>

#include "BLEService.h"

class BLECharacteristicConfig {
public:
    esp_bt_uuid_t uuid;
    const esp_gatt_perm_t permissions;
    const esp_gatt_char_prop_t properties;
    esp_attr_control_t control;
};

class BLECharacteristic {
public:
    BLECharacteristic(BLEService *service, BLECharacteristicConfig &config);
    virtual ~BLECharacteristic() {}

    void setWriteCallback(std::function<void(uint16_t len, uint8_t *value)> func);
    void setReadCallback(std::function<void(uint16_t len, uint8_t *value)> func);

    std::function<void(uint16_t len, uint8_t *value)> writeCallback;
    std::function<void(uint16_t len, uint8_t *value)> readCallback;

    esp_bt_uuid_t uuid;
    uint16_t handle;
    const esp_gatt_perm_t &permissions;
    const esp_gatt_char_prop_t &properties;
    esp_attr_control_t &control; // fixme not const to comply with API

};
