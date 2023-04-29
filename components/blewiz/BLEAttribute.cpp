#include "BLEAttribute.h"

#include <functional>

#include "esp_log.h"

static const char *TAG = "BLEAttribute";

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

// from ESP_IDF examples\bluetooth\bluedroid\ble\gatt_server\main\gatts_demo.c
// used for adding characteristic and descriptor
uint8_t dummyData[] = {0x11,0x22,0x33};
esp_attr_value_t BLEAttribute::dummyValue = {
    .attr_max_len = BLEAttribute::ATTR_MAX_LEN, // should be 0x40
    .attr_len     = sizeof(dummyValue),
    .attr_value   = dummyData,
};
