#include "BadgeService.h"

#include "esp_log.h"
#include "freertos/task.h"

#include "driver/adc.h"

static const char* LOG_TAG = "BADGE";

//.uuid = UUID16(0x2902),
//.permissions = ESP_GATT_PERM_READ | ESP_GATT_PERM_WRITE,
//.control = { .auto_rsp = ESP_GATT_RSP_BY_APP }

BLECharacteristicConfig batteryCharacteristicConfig = {
    .uuid = UUID16(0x2a19),
    .permissions = ESP_GATT_PERM_READ | ESP_GATT_PERM_WRITE,
    .properties = ESP_GATT_CHAR_PROP_BIT_READ | ESP_GATT_CHAR_PROP_BIT_WRITE | ESP_GATT_CHAR_PROP_BIT_NOTIFY,
    .control = { .auto_rsp = ESP_GATT_AUTO_RSP },
    .descriptorConfigs = {{
            .uuid = UUID16(0x2902),
            .permissions = ESP_GATT_PERM_READ | ESP_GATT_PERM_WRITE,
            .control = { .auto_rsp = ESP_GATT_RSP_BY_APP }
    }}
};

BLEDescriptorConfig bd = {
        .uuid = UUID16(0x2902),
        .permissions = ESP_GATT_PERM_READ | ESP_GATT_PERM_WRITE,
        .control = { .auto_rsp = ESP_GATT_AUTO_RSP }
};

BLECharacteristicConfig brighnessCharacteristicConfig = {
    .uuid = UUID16(0x0043),
    .permissions = ESP_GATT_PERM_READ | ESP_GATT_PERM_WRITE,
    .properties = ESP_GATT_CHAR_PROP_BIT_READ | ESP_GATT_CHAR_PROP_BIT_WRITE | ESP_GATT_CHAR_PROP_BIT_NOTIFY,
    .control = { .auto_rsp = ESP_GATT_AUTO_RSP },
    .descriptorConfigs = { }
};

BLECharacteristicConfig programCharacteristicConfig = {
    .uuid = UUID16(0x0044),
    .permissions = ESP_GATT_PERM_READ | ESP_GATT_PERM_WRITE,
    .properties = ESP_GATT_CHAR_PROP_BIT_READ | ESP_GATT_CHAR_PROP_BIT_WRITE | ESP_GATT_CHAR_PROP_BIT_NOTIFY,
    .control = { .auto_rsp = ESP_GATT_AUTO_RSP },
    .descriptorConfigs = {}
};

BadgeService::BadgeService(Display &display, AnimationProgram &animationProgram) :
    display(display),
    animationProgram(animationProgram),
    batteryCharacteristic(this, batteryCharacteristicConfig),
    batteryNotifyDesciptor(this, bd),
    brightnessCharacteristic(this, brighnessCharacteristicConfig),
    programCharacteristic(this, programCharacteristicConfig) {

    ::adc1_config_width(ADC_WIDTH_12Bit);
    ::adc1_config_channel_atten(ADC1_CHANNEL_7, ADC_ATTEN_11db); // Measure up to 2.2V
    taskHandle = NULL;
}

BadgeService::~BadgeService() {

}

void BadgeService::init() {

    batteryCharacteristic.setReadCallback(
        [this](uint16_t len, uint8_t *value) {
            ESP_LOGI(LOG_TAG, "read battery");
        }
    );

    batteryNotifyDesciptor.setWriteCallback(
            [this](uint16_t len, uint8_t *value) {
                ESP_LOGI(LOG_TAG, "write notify");
            }
    );

    brightnessCharacteristic.setWriteCallback(
        [this](uint16_t len, uint8_t *value) {
            ESP_LOGI(LOG_TAG, "set brightness");
            display.setBrightness(value[0]);
        }
    );

    programCharacteristic.setWriteCallback(
        [this](uint16_t len, uint8_t *value) {
            ESP_LOGI(LOG_TAG, "set program");
            animationProgram.setProgram(value[0]);
        }
    );

}

void BadgeService::onConnect() {
    // fixme depends on connection
    ESP_LOGI(LOG_TAG, "starting battery notify task");
    ::xTaskCreate(batteryTask, "battery", 4096, &batteryCharacteristic, tskIDLE_PRIORITY, &taskHandle);
}

void BadgeService::onDisconnect() {
    if (taskHandle != NULL) {
        ESP_LOGI(LOG_TAG, "stopping battery notify task");
        vTaskDelete(taskHandle);
        taskHandle = NULL;
    }
}

void BadgeService::batteryTask(void *parameters) {
    BLECharacteristic *batteryCharacteristic = (BLECharacteristic*)parameters;
    // todo check service, connect
    esp_gatt_if_t gatt_if = batteryCharacteristic->getService()->getGattIf();
    uint16_t conn_id = batteryCharacteristic->getService()->getConnId();
    ESP_LOGI(LOG_TAG, "battery task started: gatt_if: %d conn_id: %d", gatt_if, conn_id);

    uint8_t value[1];
    while (1) {
        esp_err_t esp_err;
        vTaskDelay(pdMS_TO_TICKS(2000));
        uint16_t handle = batteryCharacteristic->getHandle();
        if (handle == 0) {
            ESP_LOGE(LOG_TAG, "battery characteristic: no handle");
            return;
        }
        int raw = ::adc1_get_raw(ADC1_CHANNEL_7);
        // fixme check fo <0
        // based on empirical data
        const float base = 0.69;
        const float slope = 0.0015;
        const float range = 4.236;
        uint8_t percent = (base + raw * slope) / range * 100;

        value[0] = percent;
        uint16_t length = sizeof(value);
        // subsequent ESP_GATTS_SET_ATTR_VAL_EVT
        esp_err = ::esp_ble_gatts_set_attr_value(handle, length, value);
        if (esp_err != ESP_OK) {
            ESP_LOGE(LOG_TAG, "battery characteristic: set attribbte: err: %0x", esp_err);
            return;
        }
        bool need_confirm = false;
        esp_err = ::esp_ble_gatts_send_indicate(gatt_if, conn_id, handle, length, value, need_confirm);
        if (esp_err != ESP_OK) {
            ESP_LOGE(LOG_TAG, "battery characteristic: set attribbte: err: %0x", esp_err);
            return;
        }
    }
};
