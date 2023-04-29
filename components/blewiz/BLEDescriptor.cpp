#include "BLEDescriptor.h"

#include "BLEService.h"

#include "esp_log.h"
#include "esp_gap_ble_api.h"
#include "esp_gatts_api.h"

#define LOG_TAG "BLEDescriptor"

BLEDescriptor::BLEDescriptor(BLEService *service, BLEDescriptorConfig &config) :
permissions(config.permissions),
control(config.control) {
    uuid= config.uuid;
    service->attach(this);
}

// belongs to the characteristic most recently added
void BLEDescriptor::addToService(BLEService &service) {
    esp_err_t ret;
    ESP_LOGI(LOG_TAG, "add descriptor 0x%0x", uuid.uuid.uuid16);
    ret = ::esp_ble_gatts_add_char_descr(
            service.getHandle(),
            &uuid,
            permissions,
            &dummyValue,
            &control);
    if (ret) {
        ESP_LOGE(LOG_TAG, "add descriptor failed, error code: 0x%0x", ret);
    }
}

