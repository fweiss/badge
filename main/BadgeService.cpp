#include "BadgeService.h"

#include "esp_log.h"

#define LOG_TAG "BADGE"

BLECharacteristicConfig brighnessCharacteristicConfig = {
    .uuid = {
        .len = ESP_UUID_LEN_16,
        .uuid = {
            .uuid16 = 0x0043
        }
    }
};

BadgeService::BadgeService(Display &display) :
    display(display),
    brightnessCharacteristic(this, brighnessCharacteristicConfig) {
}

void BadgeService::init() {

    brightnessCharacteristic.setWriteCallback(
        [this](int p) {
            ESP_LOGI(LOG_TAG, "write requested");
            display.setBrightness(p);
        }
    );

}
