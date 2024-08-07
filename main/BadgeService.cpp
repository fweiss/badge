#include "BadgeService.h"

#include "esp_log.h"
#include "freertos/task.h"
#include "driver/adc.h"
#include "esp_ota_ops.h"

#include <cstring>
#include <string>

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
    .descriptorConfigs = {}
};

BLECharacteristicConfig programCharacteristicConfig = {
    .uuid = UUID16(0x0044),
    .permissions = ESP_GATT_PERM_READ | ESP_GATT_PERM_WRITE,
    .properties = ESP_GATT_CHAR_PROP_BIT_READ | ESP_GATT_CHAR_PROP_BIT_WRITE | ESP_GATT_CHAR_PROP_BIT_NOTIFY,
    .control = { .auto_rsp = ESP_GATT_AUTO_RSP },
    .descriptorConfigs = {{
        .uuid = UUID16(0x2902),
        .permissions = ESP_GATT_PERM_READ | ESP_GATT_PERM_WRITE,
        .control = { .auto_rsp = ESP_GATT_RSP_BY_APP }
    }}
};

BLEDescriptorConfig programIndexDescriptorConfig = {
        .uuid = UUID16(0x2902),
        .permissions = ESP_GATT_PERM_READ | ESP_GATT_PERM_WRITE,
        .control = { .auto_rsp = ESP_GATT_AUTO_RSP }
};

BLECharacteristicConfig downloadCharacteristicConfig = {
    .uuid = UUID16(0x0045),
    .permissions = ESP_GATT_PERM_WRITE,
    .properties = ESP_GATT_CHAR_PROP_BIT_WRITE,
    .control = { .auto_rsp = ESP_GATT_AUTO_RSP },
    .descriptorConfigs = {}
};

BLECharacteristicConfig paintPixelCharacteristicConfig = {
    .uuid = UUID16(0x0046),
    .permissions = ESP_GATT_PERM_WRITE,
    .properties = ESP_GATT_CHAR_PROP_BIT_WRITE,
    .control = { .auto_rsp = ESP_GATT_AUTO_RSP },
    .descriptorConfigs = {}
};

BLECharacteristicConfig paintFrameCharacteristicConfig = {
    .uuid = UUID16(0x0047),
    .permissions = ESP_GATT_PERM_WRITE,
    .properties = ESP_GATT_CHAR_PROP_BIT_WRITE,
    .control = { .auto_rsp = ESP_GATT_AUTO_RSP },
    .descriptorConfigs = {}
};

BLECharacteristicConfig appVersionCharacteristicConfig = {
    .uuid = UUID16(0x0048),
    .permissions = ESP_GATT_PERM_READ,
    .properties = ESP_GATT_CHAR_PROP_BIT_READ,
    .control = { .auto_rsp = ESP_GATT_RSP_BY_APP },
    .descriptorConfigs = { }
};

BLECharacteristicConfig frameDumpCharacteristicConfig = {
    .uuid = UUID16(0x0049),
    .permissions = ESP_GATT_PERM_READ,
    .properties = ESP_GATT_CHAR_PROP_BIT_READ,
    .control = { .auto_rsp = ESP_GATT_RSP_BY_APP },
    .descriptorConfigs = { }
};

// END OF CHARACTERISTIC CONFIGURATIONS

BadgeService::BadgeService(Display &display, AnimationProgram &animationProgram) :
    display(display),
    animationProgram(animationProgram),
    batteryCharacteristic(this, batteryCharacteristicConfig),
    batteryNotifyDesciptor(this, bd),
    brightnessCharacteristic(this, brighnessCharacteristicConfig),
    programCharacteristic(this, programCharacteristicConfig),
    programIndexDescriptor(this, programIndexDescriptorConfig),
    downloadCharacteristic(this, downloadCharacteristicConfig),
    paintPixelCharacteristic(this, paintPixelCharacteristicConfig),
    paintFrameCharacteristic(this, paintFrameCharacteristicConfig),
    appVersionCharacteristic(this, appVersionCharacteristicConfig),
    frameDumpCharacteristic(this, frameDumpCharacteristicConfig) {

    ::adc1_config_width(ADC_WIDTH_BIT_12);
    ::adc1_config_channel_atten(ADC1_CHANNEL_7, ADC_ATTEN_DB_11); // Measure up to 2.2V
    batteryTaskHandle = NULL;


}

BadgeService::~BadgeService() {

}

void BadgeService::init() {

    appVersionCharacteristic.setReadCallback(
        [this](uint16_t *len, uint8_t **value){
            const esp_app_desc_t *app_description = esp_app_get_description();
            ESP_LOGI(LOG_TAG, "version: %-16s", app_description->version);
            *len = strlen(app_description->version);
            *value = (uint8_t*) app_description->version;
        }
    );
    
    batteryCharacteristic.setReadCallback(
        [this](uint16_t *len, uint8_t **value) {
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
            ESP_LOGI(LOG_TAG, "set brightness: %d", value[0]);
            display.setBrightness(value[0]);
        }
    );

    programCharacteristic.setWriteCallback(
        [this](uint16_t len, uint8_t *value) {
            ESP_LOGI(LOG_TAG, "set program");
            animationProgram.setProgram(value[0]);
        }
    );

    downloadCharacteristic.setWriteCallback(
        [this](uint16_t len, uint8_t *value) {
            std::string data((char*)value, len);
            ESP_LOGI(LOG_TAG, "download notify: %s", (char*)data.c_str());
        }
    );

    paintPixelCharacteristic.setWriteCallback(
        [this](uint16_t len, uint8_t *value) {
            if (len < 5) {
                ESP_LOGW(LOG_TAG, "paint pixel: invalid length: %d", len);
                return;
            }
            uint16_t x = value[0];
            uint16_t y = value[1];
            Color color = (value[2] << 16) | (value[3] << 8) | (value[4]);
            // ESP_LOGI(LOG_TAG, "paint pixel: %d, %d: %xl", x, y, color);
            paintPixel->setPixelColor(x, y, color);
        }
    );
    paintFrameCharacteristic.setWriteCallback(
        [this](uint16_t len, uint8_t *value) {
            for (int j=0; j<len; j++) {
                paintFrame.emplace_back(value[j]);
            }
            // ESP_LOGI(LOG_TAG, "paint frame data: %d, size: %d", len, paintFrame.size());
            if (paintFrame.size() >= 64 * 3) {
                std::vector<uint32_t> frame;
                for (int i=0; i<64; i++) {
                    Color color = (paintFrame[3 * i + 0] << 16) | (paintFrame[3 * i + 1] << 8) | (paintFrame[3 * i +2]);
                    frame.push_back(color);
                }
                ESP_LOGI(LOG_TAG, "paint frame execute");
                paintPixel->clearFrames();
                paintPixel->setFrame(frame);
                paintFrame.clear();
            }
        }
    );

    frameDumpCharacteristic.setReadCallback(
        [this](uint16_t *len, uint8_t **value){
        static char map[] = "0123456789ABCDEF";
            const Animation *currentAnimation = animationProgram.getCurrentAnimation();
            const std::vector<uint32_t> *frame = currentAnimation->frameDump();
            ESP_LOGI(LOG_TAG, "frame dump");
            std::string json;
            json += "[";
            for (const uint32_t &color : *frame) {
                json += "\"0x";
                for (int i=20; i>=0; i-=4) {
//                for (int i=0; i<24; i+=4) {
                    json += map[(color >> i) & 0x0f];
                }
                json += "\",";
            }
            json += "]";
            ESP_LOGI(LOG_TAG, "frame dump: %s", json.c_str());
        }
    );

}

void BadgeService::onConnect() {
    // fixme depends on connection
    ESP_LOGI(LOG_TAG, "starting battery notify task");
    ::xTaskCreate(batteryTask, "battery", 4096, this, tskIDLE_PRIORITY, &batteryTaskHandle);
    // vTaskDelay(1000 / portTICK_PERIOD_MS);
    // notifyCurrentProgram();
}

void BadgeService::onDisconnect() {
    if (batteryTaskHandle != NULL) {
        ESP_LOGI(LOG_TAG, "stopping battery notify task");
        vTaskDelete(batteryTaskHandle);
        batteryTaskHandle = NULL;
    }
}

void BadgeService::onStarted() {
    const esp_app_desc_t *app_description = esp_app_get_description();
    ESP_LOGI(LOG_TAG, "version: %32s", app_description->version);
    appVersionCharacteristic.setValue(sizeof(app_description->version), (const uint8_t*)app_description->version);
}

void BadgeService::batteryTask(void *parameters) {
    // BLECharacteristic *batteryCharacteristic = (BLECharacteristic*)parameters;
    BadgeService * self = static_cast<BadgeService*>(parameters);
    BLECharacteristic *batteryCharacteristic = &self->batteryCharacteristic;
    // todo check service, connect
    esp_gatt_if_t gatt_if = batteryCharacteristic->getService()->getGattIf();
    uint16_t conn_id = batteryCharacteristic->getService()->getConnId();
    ESP_LOGI(LOG_TAG, "battery task started: gatt_if: %d conn_id: %d", gatt_if, conn_id);

    uint8_t value[1];
    while (1) {
        // esp_err_t esp_err;
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

        batteryCharacteristic->setValue(length, value);
        self->notify(*batteryCharacteristic, length, value, true);

        // subsequent ESP_GATTS_SET_ATTR_VAL_EVT
        // esp_err = ::esp_ble_gatts_set_attr_value(handle, length, value);
        // if (esp_err != ESP_OK) {
        //     ESP_LOGE(LOG_TAG, "battery characteristic: set attribbte: err: %0x", esp_err);
        //     return;
        // }
        // bool need_confirm = false;
        // esp_err = ::esp_ble_gatts_send_indicate(gatt_if, conn_id, handle, length, value, need_confirm);
        // if (esp_err != ESP_OK) {
        //     ESP_LOGE(LOG_TAG, "battery characteristic: set attribbte: err: %0x", esp_err);
        //     return;
        // }
    }
}

void BadgeService::notifyCurrentProgram() {
    ESP_LOGI(LOG_TAG, "notify current program");
    uint8_t value[1]; // fixme const
    value[0] = animationProgram.getProgramIndex();
    programCharacteristic.setValue(sizeof(value), value);
    notify(programCharacteristic, sizeof(value), value, true);
}
