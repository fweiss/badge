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
    this->serviceHandle = 0;
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
        characteristic->handle = add_char.attr_handle;
        characteristicByHandle.emplace(add_char.attr_handle, characteristic);

        if ( ! characteristicQueue.empty()) {
            addCharacteristic(characteristicQueue.front());
        }
        break;
    }
    case ESP_GATTS_READ_EVT: {
        esp_ble_gatts_cb_param_t::gatts_read_evt_param &read = param->read;
        BLECharacteristic *characteristic = characteristicByHandle.at(read.handle);
        if (characteristic == NULL) {
            ESP_LOGW(GATTS_TAG, "gatts read: not found: characteristic handle: %0x", read.handle);
            break;
        }
        ESP_LOGI(GATTS_TAG, "received read event %0x, %0x", characteristic->uuid.uuid.uuid16, read.need_rsp);

        if (read.need_rsp) {

//        esp_gatt_rsp_t rsp = {
//                .handle = read.handle,
//                .attr_value = {
//                        .len = 2,
//                };
//        };
            esp_gatt_rsp_t rsp;
            rsp.handle = read.handle;
            rsp.attr_value.len = 1;
            rsp.attr_value.value[0] = 0x22;
            esp_err_t err = ::esp_ble_gatts_send_response(gatts_if, read.conn_id, read.trans_id, ESP_GATT_OK, &rsp);
            if (err != ESP_OK) {
                ESP_LOGE(GATTS_TAG, "gatt read: response: error:  %0x", err);
            }
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
// fixme remove fake value
void BLEService::addCharacteristic(BLECharacteristic* characteristic) {
    characteristic->addToService(*this);
}
