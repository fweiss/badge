#include "BLECharacteristic.h"

#include "esp_log.h"
#include "esp_gap_ble_api.h"
#include "esp_gatts_api.h"

#define LOG_TAG "BLECharacteristic"

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

void BLECharacteristic::addToService(BLEService &service) {
    // A value is required when control is ESP_GATT_AUTO_RSP, but not for ESP_GATT_RSP_BY_APP
    // fixme remove fake value
    esp_err_t ret;
    ESP_LOGI(LOG_TAG, "adding characteristic 0x%0x", uuid.uuid.uuid16);
    uint8_t v[] = { 0x11,0x22,0x33 };
    esp_attr_value_t value = {
        .attr_max_len = ATTR_MAX_LEN,
        .attr_len     = sizeof(v),
        .attr_value   = v,
    };
    ret = ::esp_ble_gatts_add_char(
            service.getHandle(),
            &uuid,
            permissions,
            properties,
            &value,
            &control);
    if (ret) {
        ESP_LOGE(LOG_TAG, "add char failed, error code: 0x%0x", ret);
    }
}
