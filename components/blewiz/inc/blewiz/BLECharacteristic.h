#pragma once

#include <functional>

#include "BLEAttribute.h"
#include "BLEService.h"

class BLECharacteristicConfig {
public:
    const esp_bt_uuid_t uuid;
    const esp_gatt_perm_t permissions;
    const esp_gatt_char_prop_t properties;
    esp_attr_control_t control;
};

class BLECharacteristic : public BLEAttribute{
public:
    BLECharacteristic(BLEService *service, BLECharacteristicConfig &config);
    virtual ~BLECharacteristic() {}

    esp_bt_uuid_t uuid;
    const esp_gatt_perm_t &permissions;
    const esp_gatt_char_prop_t &properties;
    esp_attr_control_t &control; // fixme not const to comply with API

    void setWriteCallback(std::function<void(uint16_t len, uint8_t *value)> func);
    void setReadCallback(std::function<void(uint16_t len, uint8_t *value)> func);

protected:
    friend class BLEService;
    void addToService(BLEService &service) override;
};
