#include "BTController.h"

const char* BTController::GATTS_TAG = "BTC";

#define GATTS_DEMO_CHAR_VAL_LEN_MAX (32)

#define ERROR_CHECK(m) if (ret) { \
ESP_LOGE(GATTS_TAG, "%s %s failed: %s\n", __func__, m, esp_err_to_name(ret)); \
return; \
}

// todo refactor from unwieldy switch statement
// sequence:
// 0, 7, 12
void BTController::gatts_event_handler(esp_gatts_cb_event_t event, esp_gatt_if_t gatts_if, esp_ble_gatts_cb_param_t *param) {
    ESP_LOGI(GATTS_TAG, "gatts_event_handler: %d", event);
    switch (event) {
    case ESP_GATTS_REG_EVT: {
        ESP_LOGI(GATTS_TAG, "registering service");
        // fixme initialize in object
        esp_gatt_srvc_id_t service_id;
        service_id.is_primary = true;
        service_id.id.inst_id = 0x00;
        service_id.id.uuid.len = ESP_UUID_LEN_16;
        service_id.id.uuid.uuid.uuid16 = 0x00FF;
        uint16_t num_handle = 4;
        esp_ble_gatts_create_service(gatts_if, &service_id, num_handle);
        break;
    }
    case ESP_GATTS_CREATE_EVT: {
        ESP_LOGI(GATTS_TAG, "creating service");
        uint16_t service_handle = param->create.service_handle;
        esp_ble_gatts_start_service(service_handle);

        esp_err_t ret;
        esp_gatt_char_prop_t properties;
        esp_bt_uuid_t uuid = {
                .len = ESP_UUID_LEN_16,
                .uuid = {
                    .uuid16 = 0xff01
                }
        };
        uint8_t v[] = { 0x11,0x22,0x33 };
        esp_attr_value_t value = {
            .attr_max_len = GATTS_DEMO_CHAR_VAL_LEN_MAX,
            .attr_len     = sizeof(v),
            .attr_value   = v,
        };
        esp_attr_control_t control = { .auto_rsp = ESP_GATT_AUTO_RSP };
        esp_gatt_perm_t permissions = ESP_GATT_PERM_READ | ESP_GATT_PERM_WRITE;
        properties = ESP_GATT_CHAR_PROP_BIT_READ | ESP_GATT_CHAR_PROP_BIT_WRITE | ESP_GATT_CHAR_PROP_BIT_NOTIFY;
        ret = esp_ble_gatts_add_char(service_handle, &uuid, permissions, properties, &value, &control);
        if (ret){
            ESP_LOGE(GATTS_TAG, "add char failed, error code =%x", ret);
        }
        break;
    }
    default: {
        break;
    }
    }
}

void BTController::gap_event_handler(esp_gap_ble_cb_event_t event, esp_ble_gap_cb_param_t *param) {
    ESP_LOGI(GATTS_TAG, "gap_event_handler");
}

void BTController::init() {
    esp_err_t ret;

    esp_bt_controller_config_t bt_cfg = BT_CONTROLLER_INIT_CONFIG_DEFAULT();
    ret = esp_bt_controller_init(&bt_cfg);
    if (ret) {
        ESP_LOGE(GATTS_TAG, "%s initialize controller failed: %s\n", __func__, esp_err_to_name(ret));
        return;
    }

    ret = esp_bt_controller_enable(ESP_BT_MODE_BLE);
    ERROR_CHECK("enable controller")

    ret = esp_bluedroid_init();
    ERROR_CHECK("bluedroid init")

    ret = esp_bluedroid_enable();
    if (ret) {
        ESP_LOGE(GATTS_TAG, "%s enable bluetooth failed: %s\n", __func__, esp_err_to_name(ret));
        return;
    }

    ret = esp_ble_gatts_register_callback(gatts_event_handler);
    if (ret){
        ESP_LOGE(GATTS_TAG, "gatts register error, error code = %x", ret);
        return;
    }
    ret = esp_ble_gap_register_callback(gap_event_handler);
    if (ret){
        ESP_LOGE(GATTS_TAG, "gap register error, error code = %x", ret);
        return;
    }
    ret = esp_ble_gatts_app_register(0);
    if (ret){
        ESP_LOGE(GATTS_TAG, "gatts app register error, error code = %x", ret);
        return;
    }
    ESP_LOGI(GATTS_TAG, "bt initialized");
}
