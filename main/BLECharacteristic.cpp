#include "BLECharacteristic.h"

BLECharacteristic::BLECharacteristic(BLEService *service, BLECharacteristicConfig &config) :
    uuid(config.uuid),
    permissions(config.permissions),
    properties(config.properties),
    control(config.control) {
    service->attach(this, config);
}

void BLECharacteristic::setWriteCallback(std::function<void(uint16_t len, uint8_t *value)> func) {
    this->writeCallback = func;
}

void BLECharacteristic::setReadCallback(std::function<void(uint16_t len, uint8_t *value)> func) {
    this->readCallback = func;
}
