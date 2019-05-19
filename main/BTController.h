#pragma once

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"

#include "esp_system.h"
#include "esp_bt.h"
#include "esp_log.h"
#include "esp_gap_ble_api.h"
#include "esp_gatts_api.h"
#include "esp_bt_defs.h"
#include "esp_bt_main.h"
#include "esp_gatt_common_api.h"

class BTController {
public:
    BTController() {}
    virtual ~BTController() {}
    void init();
    static const char* GATTS_TAG;
private:
    static void gatts_event_handler(esp_gatts_cb_event_t event, esp_gatt_if_t gatts_if, esp_ble_gatts_cb_param_t *param);
    static void gap_event_handler(esp_gap_ble_cb_event_t event, esp_ble_gap_cb_param_t *param);
    void createAdvertisementData();

    // fixme referenced from static method
    static esp_ble_adv_data_t advertisementData;
    static uint8_t adv_service_uuid128[32];
    static esp_ble_adv_params_t advertisementParameters;

};
