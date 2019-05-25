#include "BadgeService.h"

BLECharacteristicConfig dimmingCharacteristicConfig = {
    .uuid = 43
};

BadgeService::BadgeService(Display &display) :
        display(display), dimmingCharacteristic(this, dimmingCharacteristicConfig) {
}

void BadgeService::init() {
    dimmingCharacteristic.setWriteCallback(
        [this](int p) {
            display.setBrightness(25);
    }
    );
}
