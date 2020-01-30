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
        ESP_LOGI(GATTS_TAG, "received write event: conn_id: %d handle: %d", write.conn_id, write.handle);
        BLEAttribute *characteristic = characteristicByHandle.at(write.handle);
        characteristic->writeCallback(write.len, write.value);
        break;
    }
    case ESP_GATTS_ADD_CHAR_EVT: {
        // todo check status
        auto &add_char = param->add_char;
        ESP_LOGI(GATTS_TAG, "received add char event: %0x", add_char.char_uuid.uuid.uuid16);

        registerNextAttribute(add_char.attr_handle);
//        BLEAttribute *characteristic = characteristicQueue.front();
//        characteristicQueue.pop();
//        characteristic->handle = add_char.attr_handle;
//        characteristicByHandle.emplace(add_char.attr_handle, characteristic);
//
//        if ( ! characteristicQueue.empty()) {
//            addCharacteristic(characteristicQueue.front());
//        }
        break;
    }
    case ESP_GATTS_ADD_CHAR_DESCR_EVT: {
        // fixme duplicate code
        // todo check status
        esp_ble_gatts_cb_param_t::gatts_add_char_descr_evt_param &add_char_descr = param->add_char_descr;
        ESP_LOGI(GATTS_TAG, "received add char desc event: %0x", add_char_descr.descr_uuid.uuid.uuid16);
        // todo assuming that front uuid is the same as that of the event
        BLEAttribute *attribute = characteristicQueue.front();
        characteristicQueue.pop();
        attribute->handle = add_char_descr.attr_handle;
        characteristicByHandle.emplace(add_char_descr.attr_handle, attribute);

        if ( ! characteristicQueue.empty()) {
            addCharacteristic(characteristicQueue.front());
        }
        break;

    }
    case ESP_GATTS_READ_EVT: {
        esp_ble_gatts_cb_param_t::gatts_read_evt_param &read = param->read;
        BLEAttribute *characteristic = characteristicByHandle.at(read.handle);
        if (characteristic == NULL) {
            ESP_LOGW(GATTS_TAG, "gatts read: not found: characteristic handle: %0x", read.handle);
            break;
        }

        ESP_LOGI(GATTS_TAG, "received read event %0x, %0x", characteristic->uuid.uuid.uuid16, read.need_rsp);
        esp_gatt_rsp_t rsp;

        uint16_t length;
        uint8_t *value;
        characteristic->readCallback(&length, &value);

        if (read.need_rsp) {

//        esp_gatt_rsp_t rsp = {
//                .handle = read.handle,
//                .attr_value = {
//                        .len = 2,
//                };
//        };
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

/**
 * The handle for the queued attributes has been established by the BLE stack.
 * Register the attribute so it can be looked up by handle.
 * Then add the next attribute, if any, to the BLE stack.
 */
void BLEService::registerNextAttribute(uint16_t attr_handle) {
    BLEAttribute *attribute = characteristicQueue.front();
    characteristicQueue.pop();
    attribute->handle = attr_handle;
    attribute->service = this;
    characteristicByHandle.emplace(attr_handle, attribute);

    if ( ! characteristicQueue.empty()) {
        BLEAttribute *next_attribute = characteristicQueue.front();
        next_attribute->addToService(*this);
    }
}

// save the characteristic in a queue for later processing via ESP_GATTS_ADD_CHAR_EVT
void BLEService::attach(BLEAttribute *attribute) {
    ESP_LOGI(GATTS_TAG, "attach: %d", attribute->uuid.uuid.uuid16);
    characteristicByUuid.emplace(attribute->uuid, attribute);
    characteristicQueue.push(attribute);
}

// A value is required when control is ESP_GATT_AUTO_RSP, but not for ESP_GATT_RSP_BY_APP
// fixme remove fake value
void BLEService::addCharacteristic(BLEAttribute* characteristic) {
    characteristic->addToService(*this);
}

void BLEService::addToService(BLEService &service) {

}
