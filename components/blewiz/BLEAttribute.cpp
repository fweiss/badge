#include "BLEAttribute.h"

#include <functional>

#include "esp_log.h"

static const char *TAG = "BLEAttribute";

BLEAttribute::BLEAttribute(const esp_bt_uuid_t &uuid) :
    uuid(uuid) {

    setReadCallback([this] (uint16_t *len, uint8_t **value) {
        ESP_LOGW(TAG, "unimplemented: read callback: uuid: %s", uuidToString().value);
    });
    setWriteCallback([this] (uint16_t len, uint8_t *value) {
        ESP_LOGW(TAG, "unimplemented: write callback: uuid: %s", uuidToString().value);
    });
}

void BLEAttribute::setWriteCallback(std::function<void(uint16_t len, uint8_t *value)> func) {
    this->writeCallback = func;
}

void BLEAttribute::setReadCallback(std::function<void(uint16_t *len, uint8_t **value)> func) {
    this->readCallback = func;
}

// maybe const v?
void BLEAttribute::setValue(const uint16_t length, const uint8_t *v) {
    ESP_LOGI(TAG, "Setting gatts attr value %d", v[0]);
    esp_err_t esp_err;
    esp_err = ::esp_ble_gatts_set_attr_value(handle, length, v);
    if (esp_err != ESP_OK) {
        ESP_LOGW(TAG, "Set attr value error: 0x%x", esp_err);
    }
}

uuidString BLEAttribute::uuidToString() {
    // could use std:string instead
    uuidString uuidString;
    char (&value)[sizeof(uuidString.value)] = uuidString.value;
    // todo branch for 16, 32, 128
    snprintf(value, sizeof(value), "%0x", uuid.uuid.uuid16);
    return uuidString;
}
