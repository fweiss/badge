#include "BadgeService.h"

#include "esp_log.h"

#define LOG_TAG "BADGE"

BLECharacteristicConfig brighnessCharacteristicConfig = {
    .uuid = UUID16(0x0043),
    .permissions = ESP_GATT_PERM_READ | ESP_GATT_PERM_WRITE,
    .properties = ESP_GATT_CHAR_PROP_BIT_READ | ESP_GATT_CHAR_PROP_BIT_WRITE | ESP_GATT_CHAR_PROP_BIT_NOTIFY,
    .control = { .auto_rsp = ESP_GATT_AUTO_RSP }
};

BLECharacteristicConfig programCharacteristicConfig = {
    .uuid = UUID16(0x0044),
    .permissions = ESP_GATT_PERM_READ | ESP_GATT_PERM_WRITE,
    .properties = ESP_GATT_CHAR_PROP_BIT_READ | ESP_GATT_CHAR_PROP_BIT_WRITE | ESP_GATT_CHAR_PROP_BIT_NOTIFY,
    .control = { .auto_rsp = ESP_GATT_AUTO_RSP }
};

BadgeService::BadgeService(Display &display, AnimationProgram &animationProgram) :
    display(display),
    animationProgram(animationProgram),
    brightnessCharacteristic(this, brighnessCharacteristicConfig),
    programCharacteristic(this, programCharacteristicConfig) {
}

void BadgeService::init() {

    brightnessCharacteristic.setWriteCallback(
        [this](uint16_t len, uint8_t *value) {
            ESP_LOGI(LOG_TAG, "write requested");
            display.setBrightness(value[0]);
        }
    );

    programCharacteristic.setWriteCallback(
        [this](uint16_t len, uint8_t *value) {
            ESP_LOGI(LOG_TAG, "change program requested");
            animationProgram.setProgram(value[0]);
        }
    );

}
