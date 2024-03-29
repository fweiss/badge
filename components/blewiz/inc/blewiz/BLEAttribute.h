#pragma once

// #include "BLEService.h"
class BLEService;

#include <functional>

#include "esp_gatts_api.h"

class BLEAttribute {
public:
    BLEAttribute() {}
    virtual ~BLEAttribute() {}

    static const uint16_t ATTR_MAX_LEN = 16;

    uint16_t getHandle() { return this->handle; }
    BLEService *getService() { return this->service; }

    void setWriteCallback(std::function<void(uint16_t len, uint8_t *value)> func);
    void setReadCallback(std::function<void(uint16_t *len, uint8_t **value)> func);

    // should be protected and allowed access from BLESerive subclass
    // maybe const value?
    void setValue(const uint16_t length, const uint8_t *value);

protected:
    friend class BLEService;

    uint16_t handle = 0;
    esp_bt_uuid_t uuid;
    BLEService *service;

    static esp_attr_value_t dummyValue;

    virtual void addToService(BLEService &service) = 0;
    std::function<void(uint16_t len, uint8_t *value)> writeCallback;
    std::function<void(uint16_t *len, uint8_t **value)> readCallback;

};
