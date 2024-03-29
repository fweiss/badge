#pragma once

#include <functional>
#include <vector>

#include "BLEAttribute.h"
#include "BLEDescriptor.h"
#include "BLEService.h"

class BLECharacteristicConfig {
public:
    const esp_bt_uuid_t uuid;
    const esp_gatt_perm_t permissions;
    const esp_gatt_char_prop_t properties;
    esp_attr_control_t control;
    std::vector<BLEDescriptorConfig> descriptorConfigs;
};

class BLECharacteristic : public BLEAttribute {
public:
    BLECharacteristic(BLEService *service, BLECharacteristicConfig &config);
    virtual ~BLECharacteristic() {}

    const esp_gatt_perm_t &permissions;
    const esp_gatt_char_prop_t &properties;
    esp_attr_control_t &control; // fixme not const to comply with API

protected:
    friend class BLEService;
    void addToService(BLEService &service) override;
};
