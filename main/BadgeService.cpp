#include "BadgeService.h"

#include "esp_log.h"

#define LOG_TAG "BADGE"

BLECharacteristicConfig brighnessCharacteristicConfig = {
    .uuid = UUID16(0x0043),
    .permissions = ESP_GATT_PERM_READ | ESP_GATT_PERM_WRITE,
    .properties = ESP_GATT_CHAR_PROP_BIT_READ | ESP_GATT_CHAR_PROP_BIT_WRITE | ESP_GATT_CHAR_PROP_BIT_NOTIFY,
//    .control = { .auto_rsp = ESP_GATT_RSP_BY_APP } // in case of ESP_GATT_AUTO_RSP, need a default value
    .control = { .auto_rsp = ESP_GATT_AUTO_RSP } // in case of ESP_GATT_AUTO_RSP, need a default value
};

BLECharacteristicConfig programCharacteristicConfig = {
    .uuid = UUID16(0x0044),
    .permissions = ESP_GATT_PERM_READ | ESP_GATT_PERM_WRITE,
    .properties = ESP_GATT_CHAR_PROP_BIT_READ | ESP_GATT_CHAR_PROP_BIT_WRITE | ESP_GATT_CHAR_PROP_BIT_NOTIFY,
    .control = { .auto_rsp = ESP_GATT_AUTO_RSP } // in case of ESP_GATT_AUTO_RSP, need a default value
};

BadgeService::BadgeService(Display &display) :
    display(display),
    brightnessCharacteristic(this, brighnessCharacteristicConfig),
    programCharacteristic(this, programCharacteristicConfig) {
}

void BadgeService::init() {

    brightnessCharacteristic.setWriteCallback(
        [this](int p) {
            ESP_LOGI(LOG_TAG, "write requested");
            display.setBrightness(p);
        }
    );

    programCharacteristic.setWriteCallback(
        [this](int p) {
            ESP_LOGI(LOG_TAG, "change program requested");
        }
    );

}
