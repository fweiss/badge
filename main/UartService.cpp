#include "UartService.h"

BLECharacteristicConfig rxCharacteristicConfig = {
    .uuid = {
        .len = ESP_UUID_LEN_128,
        .uuid = {
            .uuid128 = 
                { 0x6E, 0x40, 0x00, 0x02, 0xB5, 0xA3, 0xF3, 0x93, 0xE0, 0xA9, 0xE5, 0x0E, 0x24, 0xDC, 0xCA, 0x9E },
        }
    },
    .permissions = ESP_GATT_PERM_READ,
    .properties = ESP_GATT_CHAR_PROP_BIT_READ,
    .control = { .auto_rsp = ESP_GATT_RSP_BY_APP },
    .descriptorConfigs = { }
};

BLECharacteristicConfig txCharacteristicConfig = {
    .uuid = {
        .len = ESP_UUID_LEN_128, 
        .uuid = { 
            .uuid128 =         
            { 0x6E, 0x40, 0x00, 0x03, 0xB5, 0xA3, 0xF3, 0x93, 0xE0, 0xA9, 0xE5, 0x0E, 0x24, 0xDC, 0xCA, 0x9E },
        }
    },
    .permissions = ESP_GATT_PERM_WRITE,
    .properties = ESP_GATT_CHAR_PROP_BIT_WRITE,
    .control = { .auto_rsp = ESP_GATT_RSP_BY_APP },
    .descriptorConfigs = { }
};

UartService::UartService() :
    rxCharacteristic(this, rxCharacteristicConfig),
    txCharacteristic(this, txCharacteristicConfig) {

}

UartService::~UartService() {

}