#include "BLEAttribute.h"

#include <functional>

void BLEAttribute::setWriteCallback(std::function<void(uint16_t len, uint8_t *value)> func) {
    this->writeCallback = func;
}

void BLEAttribute::setReadCallback(std::function<void(uint16_t len, uint8_t *value)> func) {
    this->readCallback = func;
}
