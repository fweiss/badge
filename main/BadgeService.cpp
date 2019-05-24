#include "BadgeService.h"

BLECharacteristicConfig dimmingCharacteristicConfig;

BadgeService::BadgeService() : dimmingCharacteristic(dimmingCharacteristicConfig) {
    // create service
}

void BadgeService::init() {
    // create dim characteristic
    // add write handler
    dimmingCharacteristic.onWrite(
        [](int p) {
            // display.setDim();
    }
    );
}
