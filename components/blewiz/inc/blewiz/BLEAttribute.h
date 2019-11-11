#pragma once

#include "BLEService.h"

#include <functional>

class BLEAttribute {
public:
    BLEAttribute() {}
    virtual ~BLEAttribute() {}

    static const uint16_t ATTR_MAX_LEN = 16;

    uint16_t getHandle() { return this->handle; }

protected:
    friend class BLEService;

    uint16_t handle = 0;
    esp_bt_uuid_t uuid;

    virtual void addToService(BLEService &service) = 0;
    std::function<void(uint16_t len, uint8_t *value)> writeCallback;
    std::function<void(uint16_t len, uint8_t *value)> readCallback;
};
