#pragma once

#include "BLEAttribute.h"

class BLEDescriptorConfig {
public:
    esp_bt_uuid_t uuid;
    const esp_gatt_perm_t permissions;
    esp_attr_control_t control;
};

class BLEDescriptor : public BLEAttribute {
public:
    BLEDescriptor(BLEService *service, BLEDescriptorConfig &config);
    virtual ~BLEDescriptor() {}

    esp_bt_uuid_t uuid;
    uint16_t handle = 0;
    const esp_gatt_perm_t &permissions;
    esp_attr_control_t &control; // fixme not const to comply with API

protected:
    friend class BLEService;
    void addToService(BLEService &service) override;
};
