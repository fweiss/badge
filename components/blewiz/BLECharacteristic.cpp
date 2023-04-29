#include "BLECharacteristic.h"

#include "esp_log.h"
#include "esp_gap_ble_api.h"
#include "esp_gatts_api.h"

#define LOG_TAG "BLECharacteristic"

BLECharacteristic::BLECharacteristic(BLEService *service, BLECharacteristicConfig &config) :
permissions(config.permissions),
properties(config.properties),
control(config.control) {
    uuid = config.uuid;
    service->attach(this);
}

void BLECharacteristic::addToService(BLEService &service) {
    // A value is required when control is ESP_GATT_AUTO_RSP, but not for ESP_GATT_RSP_BY_APP
    // fixme remove fake value
    esp_err_t ret;
    ESP_LOGI(LOG_TAG, "adding characteristic 0x%0x", uuid.uuid.uuid16);
    ret = ::esp_ble_gatts_add_char(
            service.getHandle(),
            &uuid,
            permissions,
            properties,
            &dummyValue,
            &control);
    if (ret) {
        ESP_LOGE(LOG_TAG, "add char failed, error code: 0x%0x", ret);
    }
}
