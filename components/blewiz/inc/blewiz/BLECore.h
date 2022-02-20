#pragma once

#include "esp_bt.h"
#include "esp_gap_ble_api.h"
#include "esp_gatts_api.h"
#include "esp_bt_main.h"

#include "BLEService.h"

class BLECore {
public:
    BLECore();
    virtual ~BLECore() {}

    void init();
    void registerService(BLEService *service) { BLECore::service = service; }

    static BLEService *service; // public, for now

private:
    static const char* LOG_TAG;

    static void gatts_event_handler(esp_gatts_cb_event_t event, esp_gatt_if_t gatts_if, esp_ble_gatts_cb_param_t *param);
    static void gap_event_handler(esp_gap_ble_cb_event_t event, esp_ble_gap_cb_param_t *param);

    // fixme referenced from static method
    static esp_ble_adv_data_t advertisementData;
    static uint8_t adv_service_uuid128[32];
    static esp_ble_adv_params_t advertisementParameters;

    void initDevice();
    void initBluedroid();
    void initCallbacks();
    void initSpp();
    void registerApp();

    static void addService(BLEService *service, esp_gatt_if_t gatts_if);


};
