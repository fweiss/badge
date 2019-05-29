#include "BadgeService.h"

BLECharacteristicConfig brighnessCharacteristicConfig = {
    .uuid = 43
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
