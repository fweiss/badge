#pragma once

#include "esp_spp_api.h"

class BLESpp {
public:
    BLESpp();
    ~BLESpp();

    static void registerCallbacks();
    static void init();
private:
    static const esp_spp_mode_t esp_spp_mode = ESP_SPP_MODE_CB;

    static void esp_spp_cb(esp_spp_cb_event_t event, esp_spp_cb_param_t *param);
};
