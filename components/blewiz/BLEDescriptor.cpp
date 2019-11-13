#include "BLEDescriptor.h"

#include "esp_log.h"
#include "esp_gap_ble_api.h"
#include "esp_gatts_api.h"

#define LOG_TAG "BLEDescriptor"

BLEDescriptor::BLEDescriptor(BLEService *service, BLEDescriptorConfig &config) :
    uuid(config.uuid),
    permissions(config.permissions),
    control(config.control) {
    service->attach(this);
}

// belongs to the characteristic most recently added
void BLEDescriptor::addToService(BLEService &service) {
    // A value is required when control is ESP_GATT_AUTO_RSP, but not for ESP_GATT_RSP_BY_APP
    // fixme remove fake value
    esp_err_t ret;
    ESP_LOGI(LOG_TAG, "add descriptor 0x%0x", uuid.uuid.uuid16);
    uint8_t v[] = { 0x01, 0x00 }; // notify
    esp_attr_value_t value = {
        .attr_max_len = ATTR_MAX_LEN,
        .attr_len     = sizeof(v),
        .attr_value   = v,
    };
    ret = ::esp_ble_gatts_add_char_descr(
            service.getHandle(),
            &uuid,
            permissions,
            &value,
            &control);
    if (ret) {
        ESP_LOGE(LOG_TAG, "add descriptor failed, error code: 0x%0x", ret);
    }
}

