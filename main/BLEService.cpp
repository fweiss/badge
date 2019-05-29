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

BLEService::BLEService() {

}

void BLEService::handleGattsEvent(esp_gatts_cb_event_t event, esp_gatt_if_t gatts_if, esp_ble_gatts_cb_param_t *param) {

}

void BLEService::attach(BLECharacteristic *characteristic, BLECharacteristicConfig &config) {
    characteristics.insert({config.uuid, characteristic});

    esp_err_t ret;

    esp_bt_uuid_t uuid = {
            .len = ESP_UUID_LEN_16,
            .uuid = {
                .uuid16 = 0xff01
            }
    };
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

void BLEService::onCharacteristicRead(int uuid) {
    BLECharacteristic *characteristic = characteristics.at(uuid);
    characteristic->readCallback(7);
}

void BLEService::onCharacteristicWrite(struct esp_ble_gatts_cb_param_t::gatts_write_evt_param param) {
    uint16_t characteristicHandle = param.handle;
    BLECharacteristic *characteristic = characteristics.at(characteristicHandle);
    characteristic->writeCallback(8);
}
