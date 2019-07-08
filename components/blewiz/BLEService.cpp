#include "BLEService.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "esp_log.h"

#include "esp_bt.h"
#include "esp_gap_ble_api.h"
#include "esp_gatts_api.h"
#include "esp_bt_main.h"

#include "BLECharacteristic.h"

static const char* GATTS_TAG = "BLEService";

BLEService::BLEService() : characteristicByUuid(), characteristicByHandle(), characteristicQueue() {

}

void BLEService::handleGattsEvent(esp_gatts_cb_event_t event, esp_gatt_if_t gatts_if, esp_ble_gatts_cb_param_t *param) {
    switch (event) {
    case ESP_GATTS_CREATE_EVT:
        ESP_LOGI(GATTS_TAG, "creating service: %d", param->create.service_handle);
        serviceHandle = param->create.service_handle;
        if ( ! characteristicQueue.empty()) {
            addCharacteristic(characteristicQueue.front());
        }
        break;
    case ESP_GATTS_WRITE_EVT: {
        auto &write = param->write;
        ESP_LOGI(GATTS_TAG, "received write event");
        BLECharacteristic *characteristic = characteristicByHandle.at(write.handle);
        characteristic->writeCallback(write.len, write.value);
        break;
    }
    case ESP_GATTS_ADD_CHAR_EVT: {
        // todo check status
        auto &add_char = param->add_char;
        ESP_LOGI(GATTS_TAG, "received add char event: %0x", add_char.char_uuid.uuid.uuid16);
//        BLECharacteristic *characteristic = characteristicByUuid.at(add_char.char_uuid);
        BLECharacteristic *characteristic = characteristicQueue.front();
        characteristicQueue.pop();
        characteristicByHandle.emplace(add_char.attr_handle, characteristic);

        if ( ! characteristicQueue.empty()) {
            addCharacteristic(characteristicQueue.front());
        }
        break;
    }
    default:
        break;
    }
}

// save the characteristic in a queue for later processing via ESP_GATTS_ADD_CHAR_EVT
void BLEService::attach(BLECharacteristic *characteristic, BLECharacteristicConfig &config) {
    ESP_LOGI(GATTS_TAG, "attach: %d", config.uuid.uuid.uuid16);
    characteristicByUuid.emplace(config.uuid, characteristic);
    characteristicQueue.push(characteristic);
}

// A value is required when control is ESP_GATT_AUTO_RSP, but not for ESP_GATT_RSP_BY_APP
void BLEService::addCharacteristic(BLECharacteristic* characteristic) {
    esp_err_t ret;
    ESP_LOGI(GATTS_TAG, "adding characteristic 0x%0x", characteristic->uuid.uuid.uuid16);
    uint8_t v[] = { 0x11,0x22,0x33 };
    esp_attr_value_t value = {
        .attr_max_len = ATTR_MAX_LEN,
        .attr_len     = sizeof(v),
        .attr_value   = v,
    };
    ret = esp_ble_gatts_add_char(
            serviceHandle,
            &characteristic->uuid,
            characteristic->permissions,
            characteristic->properties,
            &value,
            &characteristic->control);
    if (ret) {
        ESP_LOGE(GATTS_TAG, "add char failed, error code: 0x%0x", ret);
    }

}
