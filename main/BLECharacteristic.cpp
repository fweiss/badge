#include "BLECharacteristic.h"

BLECharacteristic::BLECharacteristic(BLEService *service, BLECharacteristicConfig &config) :
    permissions(config.permissions),
    properties(config.properties),
    control(config.control) {
//    this->permissions = ESP_GATT_PERM_READ | ESP_GATT_PERM_WRITE;
//    properties = ESP_GATT_CHAR_PROP_BIT_READ | ESP_GATT_CHAR_PROP_BIT_WRITE | ESP_GATT_CHAR_PROP_BIT_NOTIFY;
//    uint8_t v[] = { 0x11,0x22,0x33 };

//    esp_attr_value_t value = {
//        .attr_max_len = ATTR_MAX_LEN,
//        .attr_len     = sizeof(v),
//        .attr_value   = v,
//    };

//    control = { .auto_rsp = ESP_GATT_AUTO_RSP };
    service->attach(this, config);
}

void BLECharacteristic::setWriteCallback(std::function<void(int)> func) {
    this->writeCallback = func;
}

void BLECharacteristic::setReadCallback(std::function<void(int)> func) {
    this->readCallback = func;
}
