#pragma once

//#include "BLEService.h"
class BLEService;

#include <functional>

#include "esp_gatts_api.h"

typedef struct {
    char value[32+4+1];
} uuidString;

class BLEAttribute {
public:
    // maybe use config struct instead
    BLEAttribute(const esp_bt_uuid_t &uuid);
    virtual ~BLEAttribute() {}

    static const uint16_t ATTR_MAX_LEN = 16;

    uint16_t getHandle() { return this->handle; }
    BLEService *getService() { return this->service; }
    uuidString uuidToString();

    void setWriteCallback(std::function<void(uint16_t len, uint8_t *value)> func);
    void setReadCallback(std::function<void(uint16_t *len, uint8_t **value)> func);

    // should be protected and allowed access from BLESerive subclass
    // maybe const value?
    void setValue(const uint16_t length, const uint8_t *value);

    // fixme make protected or private
    const esp_bt_uuid_t &uuid;

protected:
    friend class BLEService;

    uint16_t handle = 0;
    BLEService *service;

    virtual void addToService(BLEService &service) = 0;
    std::function<void(uint16_t len, uint8_t *value)> writeCallback;
    std::function<void(uint16_t *len, uint8_t **value)> readCallback;

};
