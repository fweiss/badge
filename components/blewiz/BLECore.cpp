#include "BLECore.h"

#include "BLEService.h"
#include "BLESpp.h"

#include "esp_log.h"
#include "esp_bt_device.h"
#include "esp_gatt_defs.h"

#include <algorithm>

const char* BLECore::LOG_TAG = "BLECore";

#define ERROR_CHECK(m) if (ret) { \
ESP_LOGE(LOG_TAG, "%s %s failed: %s\n", __func__, m, esp_err_to_name(ret)); \
return; \
}

// e.g. esp_ble_gatts_cb_param_t::gatts_connect_evt_param &connect = param->connect;
#define GATT_EVT_PARAM(name, type) esp_ble_gatts_cb_param_t:: ## type & ## name = param-> ## name;

BLECore::BLECore() {

}

BLEService* BLECore::service = NULL;

void BLECore::init() {
    initDevice();
    initBluedroid();
    initCallbacks();
    initSpp(); // to do optional
    registerApp();
}

// outline for Service elaboration
// advertising could be separate?
//
void BLECore::gatts_event_handler(esp_gatts_cb_event_t event, esp_gatt_if_t gatts_if, esp_ble_gatts_cb_param_t *param) {
    esp_err_t ret;

    ESP_LOGI(LOG_TAG, "gatts_event_handler: %d", event);

    service->handleGattsEvent(event, gatts_if, param);

    switch (event) {
    case ESP_GATTS_REG_EVT: {
        ESP_LOGI(LOG_TAG, "registering service");

        ret = esp_ble_gap_config_adv_data(&advertisementData);
        ERROR_CHECK("configure advertising data");

        // fixme initialize in object
//        esp_gatt_srvc_id_t service_id;
//        service_id.is_primary = true;
//        service_id.id.inst_id = 0x00;
//        service_id.id.uuid.len = ESP_UUID_LEN_16;
//        service_id.id.uuid.uuid.uuid16 = 0x00FF;
//        uint16_t num_handle = 14;
//        esp_ble_gatts_create_service(gatts_if, &service_id, num_handle);
        // if null
        if (service != NULL) {
            addService(service, gatts_if);
        }
        else {
            ESP_LOGW(LOG_TAG, "no service to add");
        }
        break;
    }
    case ESP_GATTS_CREATE_EVT: {
        ESP_LOGI(LOG_TAG, "creating service");
        uint16_t service_handle = param->create.service_handle;
        esp_ble_gatts_start_service(service_handle);
        break;
    }
    case ESP_GATTS_START_EVT: {
        ESP_LOGI(LOG_TAG, "service started");
        service->onStarted();
        break;
    }
    case ESP_GATTS_ADD_CHAR_EVT: {
//        ESP_LOGI(GATTS_TAG, "characteristic added");
        break;
    }
    case ESP_GATTS_CONNECT_EVT: {
        esp_ble_gatts_cb_param_t::gatts_connect_evt_param &connect = param->connect;
        ESP_LOGI(LOG_TAG, "connect occurred: conn_id: %d", connect.conn_id);
        service->conn_id = connect.conn_id;
        service->onConnect();
//        esp_ble_gap_update_conn_params(&conn_params);
        break;
    }
    case ESP_GATTS_DISCONNECT_EVT: {
        auto &disconnect = param->disconnect;
        ESP_LOGI(LOG_TAG, "discconnect occurred: reason: %d", disconnect.reason);
        service->onDisconnect();
        esp_ble_gap_start_advertising(&advertisementParameters);
        ESP_LOGI(LOG_TAG, "advertising started");
        // todo zero conn_id
        break;
    }
    default: {
        break;
    }
    }
}

void BLECore::gap_event_handler(esp_gap_ble_cb_event_t event, esp_ble_gap_cb_param_t *param) {
    esp_err_t ret;

    ESP_LOGI(LOG_TAG, "gap_event_handler: %d", event);

    switch (event) {
    case ESP_GAP_BLE_ADV_DATA_SET_COMPLETE_EVT: {
        ret = esp_ble_gap_start_advertising(&advertisementParameters);
        ERROR_CHECK("start advertising")
        ESP_LOGI(LOG_TAG, "starting ble advertisement");
        break;
    }
    case ESP_GAP_BLE_ADV_START_COMPLETE_EVT: {
        ESP_LOGI(LOG_TAG, "ble advertisement started");
        break;
    }
    case ESP_GAP_BLE_UPDATE_CONN_PARAMS_EVT: {
        ESP_LOGI(LOG_TAG, "ble update connection parameters");
        break;
    }
    default: {
        break;
    }
    }
}

void BLECore::initDevice() {
    esp_err_t ret;

    esp_bt_controller_config_t bt_cfg = BT_CONTROLLER_INIT_CONFIG_DEFAULT();
    ret = esp_bt_controller_init(&bt_cfg);
    if (ret) {
        ESP_LOGE(LOG_TAG, "%s initialize controller failed: %s\n", __func__, esp_err_to_name(ret));
        return;
    }

    ret = esp_bt_controller_enable(ESP_BT_MODE_BLE);
    ERROR_CHECK("enable controller")

    ret = esp_bluedroid_init();
    ERROR_CHECK("bluedroid init")

    ret = esp_bluedroid_enable();
    if (ret) {
        ESP_LOGE(LOG_TAG, "%s enable bluetooth failed: %s\n", __func__, esp_err_to_name(ret));
        return;
    }
    const uint8_t* address = esp_bt_dev_get_address();
    ESP_LOGI(LOG_TAG, "bluetooth device address: %x:%x:%x:%x:%x:%x", address[0], address[1], address[2], address[3], address[4], address[5]);
    esp_bt_dev_set_device_name("Badge");

    ret = esp_ble_gatts_register_callback(gatts_event_handler);
    if (ret){
        ESP_LOGE(LOG_TAG, "gatts register error, error code = %x", ret);
        return;
    }
    ret = esp_ble_gap_register_callback(gap_event_handler);
    if (ret){
        ESP_LOGE(LOG_TAG, "gap register error, error code = %x", ret);
        return;
    }
    ESP_LOGI(LOG_TAG, "bt initialized");
}
void BLECore::initBluedroid() {

}
void BLECore::initCallbacks() {

}

void BLECore::initSpp() {
    // BLESpp::registerCallbacks();
    // BLESpp::init();
 }

void BLECore::registerApp() {
    esp_err_t ret;
    ESP_LOGI(LOG_TAG, "registering app server");
    ret = esp_ble_gatts_app_register(0);
    if (ret) {
        ESP_LOGE(LOG_TAG, "gatts app register error, error code = %x", ret);
        return;
    }
}

void BLECore::addService(BLEService *service, esp_gatt_if_t gatts_if) {

    service->gatt_if = gatts_if;

    // init here?
    // fixme parameterize service uuid
    esp_gatt_srvc_id_t service_id;
    service_id.is_primary = true;
    service_id.id.inst_id = 0x00;

    service_id.id.uuid = service->uuid;  // copy
    // todo move this to BLEAttribute constructor
    if (service_id.id.uuid.len == ESP_UUID_LEN_128) {
        std::vector<uint8_t> bare(service->uuid.uuid.uuid128, service->uuid.uuid.uuid128 + 128/8);
        std::reverse(bare.begin(), bare.end());
        int i = 0;
        for (auto byte : bare) {
            service_id.id.uuid.uuid.uuid128[i++] = byte;
        }
    }

    uint16_t num_handle = 20;
    esp_ble_gatts_create_service(gatts_if, &service_id, num_handle);
}

uint8_t BLECore::adv_service_uuid128[32] = {
    /* LSB <--------------------------------------------------------------------------------> MSB */
    //first uuid, 16bit, [12],[13] is the value
    0xfb, 0x34, 0x9b, 0x5f, 0x80, 0x00, 0x00, 0x80, 0x00, 0x10, 0x00, 0x00, 0xEE, 0x00, 0x00, 0x00,
    //second uuid, 32bit, [12], [13], [14], [15] is the value
    0xfb, 0x34, 0x9b, 0x5f, 0x80, 0x00, 0x00, 0x80, 0x00, 0x10, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00,
};

esp_ble_adv_data_t BLECore::advertisementData = {
    .set_scan_rsp = false,
    .include_name = true,
    .include_txpower = true,
    .min_interval = 0x20,
    .max_interval = 0x40,
    .appearance = 0x00,
    .manufacturer_len = 0, //TEST_MANUFACTURER_DATA_LEN,
    .p_manufacturer_data =  NULL, //&test_manufacturer[0],
    .service_data_len = 0,
    .p_service_data = NULL,
    .service_uuid_len = 32,
    .p_service_uuid = adv_service_uuid128,
    .flag = (ESP_BLE_ADV_FLAG_GEN_DISC | ESP_BLE_ADV_FLAG_BREDR_NOT_SPT),
};

esp_ble_adv_params_t BLECore::advertisementParameters = {
    .adv_int_min        = 0x20,
    .adv_int_max        = 0x40,
    .adv_type           = ADV_TYPE_IND,
    .own_addr_type      = BLE_ADDR_TYPE_PUBLIC,
    .peer_addr            = { 0 },
    .peer_addr_type       = BLE_ADDR_TYPE_RANDOM,
    .channel_map        = ADV_CHNL_ALL,
    .adv_filter_policy = ADV_FILTER_ALLOW_SCAN_ANY_CON_ANY,
};

