#include "BadgeService.h"

BLECharacteristicConfig brighnessCharacteristicConfig = {
    .uuid = {
        .len = ESP_UUID_LEN_16,
        .uuid = {
            .uuid16 = 0x0043
        }
    }
};

BadgeService::BadgeService(Display &display) :
        display(display), brightnessCharacteristic(this, brighnessCharacteristicConfig) {
}

void BadgeService::init() {

    brightnessCharacteristic.setWriteCallback(
        [this](int p) {
            display.setBrightness(25);
        }
    );

}
