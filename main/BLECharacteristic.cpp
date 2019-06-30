#include "BLECharacteristic.h"

BLECharacteristic::BLECharacteristic(BLEService *service, BLECharacteristicConfig &config) {
    // get config data here
    service->attach(this, config);
}

void BLECharacteristic::setWriteCallback(std::function<void(int)> func) {
    this->writeCallback = func;
}

void BLECharacteristic::setReadCallback(std::function<void(int)> func) {
    this->readCallback = func;
}
