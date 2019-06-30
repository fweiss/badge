#include "BLEService.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "esp_log.h"

#include "esp_bt.h"
#include "esp_gap_ble_api.h"
#include "esp_gatts_api.h"
#include "esp_bt_main.h"

#include "BLECharacteristic.h"

#define GATTS_TAG "BLEService"

BLEService::BLEService() : characteristicByUuid(), characteristicByHandle() {

}

void BLEService::handleGattsEvent(esp_gatts_cb_event_t event, esp_gatt_if_t gatts_if, esp_ble_gatts_cb_param_t *param) {
    switch (event) {
//    case ESP_GATTS_ADD_CHAR_EVT:
//        onCharacteristicAdd(gatts_if, param->add_char);
//        break;
    case ESP_GATTS_CREATE_EVT:
        ESP_LOGI(GATTS_TAG, "creating service: %d", param->create.service_handle);
        serviceHandle = param->create.service_handle;
        addCharacteristics();
        break;
    case ESP_GATTS_WRITE_EVT: {
        ESP_LOGI(GATTS_TAG, "received write event");
        auto &write = param->write;
        // handle, len, value
        BLECharacteristic *characteristic = characteristicByHandle.at(write.handle);
        characteristic->writeCallback(write.value[0]);
        break;
    }
    case ESP_GATTS_ADD_CHAR_EVT: {
        auto &add_char = param->add_char;
        ESP_LOGI(GATTS_TAG, "received add char event");
        BLECharacteristic *characteristic = characteristicByUuid.at(add_char.char_uuid);
        characteristicByHandle.insert({ add_char.attr_handle, characteristic });
        break;
    }
    default:
        break;
    }
}

void BLEService::onCharacteristicAdd(esp_gatt_if_t gatts_if, esp_ble_gatts_cb_param_t::gatts_add_char_evt_param &addChar) {
    ESP_LOGI(GATTS_TAG, "onCharacteristicAdd: %d", addChar.char_uuid.uuid.uuid16);
    // todo log error status
    if (addChar.status == ESP_GATT_OK) {
        BLECharacteristic *characteristic = characteristicByUuid.at(addChar.char_uuid);
        characteristicByHandle.insert({addChar.attr_handle, characteristic});
        (void)addChar.service_handle;
        ;
    }
}

void BLEService::attach(BLECharacteristic *characteristic, BLECharacteristicConfig &config) {
    ESP_LOGI(GATTS_TAG, "attach: %d", config.uuid.uuid.uuid16);
    characteristicByUuid.insert({config.uuid, characteristic});
}


void BLEService::onCharacteristicRead(int uuid) {
//    BLECharacteristic *characteristic = characteristicsByUuid.at(uuid);
//    characteristic->readCallback(7);
}

void BLEService::onCharacteristicWrite(struct esp_ble_gatts_cb_param_t::gatts_write_evt_param param) {
    uint16_t characteristicHandle = param.handle;
    BLECharacteristic *characteristic = characteristicByHandle.at(characteristicHandle);
    characteristic->writeCallback(8);
}

void BLEService::addCharacteristics() {
    esp_bt_uuid_t uuid = {
            .len = ESP_UUID_LEN_16,
            .uuid = {
                .uuid16 = 0x0043
            }
        };

    BLECharacteristic *characteristic = characteristicByUuid.at(uuid);
    esp_err_t ret;

//    esp_bt_uuid_t &uuid = characteristic->uuid;
    esp_gatt_perm_t permissions = ESP_GATT_PERM_READ | ESP_GATT_PERM_WRITE;
    esp_gatt_char_prop_t properties;
    properties = ESP_GATT_CHAR_PROP_BIT_READ | ESP_GATT_CHAR_PROP_BIT_WRITE | ESP_GATT_CHAR_PROP_BIT_NOTIFY;
    uint8_t v[] = { 0x11,0x22,0x33 };
    esp_attr_value_t value = {
        .attr_max_len = ATTR_MAX_LEN,
        .attr_len     = sizeof(v),
        .attr_value   = v,
    };
    esp_attr_control_t control = { .auto_rsp = ESP_GATT_AUTO_RSP };

    ret = esp_ble_gatts_add_char(serviceHandle, &uuid, permissions, properties, &value, &control);
    if (ret) {
        ESP_LOGE(GATTS_TAG, "add char failed, error code =%x", ret);
    }
}
