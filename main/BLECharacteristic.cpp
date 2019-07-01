#include "BLECharacteristic.h"

BLECharacteristic::BLECharacteristic(BLEService *service, BLECharacteristicConfig &config) :
    permissions(config.permissions),
    properties(config.properties),
    control(config.control) {
    service->attach(this, config);
}

void BLECharacteristic::setWriteCallback(std::function<void(int)> func) {
    this->writeCallback = func;
}

void BLECharacteristic::setReadCallback(std::function<void(int)> func) {
    this->readCallback = func;
}
