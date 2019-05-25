#include "BadgeService.h"

BLECharacteristicConfig dimmingCharacteristicConfig = {
    .uuid = 43
};

BadgeService::BadgeService() : dimmingCharacteristic(this, dimmingCharacteristicConfig) {
    // create service
}

void BadgeService::init() {
    dimmingCharacteristic.onWrite(
        [](int p) {
            // display.setDim();
    }
    );
}
