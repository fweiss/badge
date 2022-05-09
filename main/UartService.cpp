#include "UartService.h"
#include "esp_log.h"
#include <cstring>

const char* XTAG = "UartService";

/**
 * @brief Used at compile time to flip a big-endian array of bytes
 * to a little-endian UUID structure.
 * We expect the compiler to optimize this out of the generated code.
 * 
 * @param the UUID as an array of big-endian bytes 
 * @return constexpr esp_bt_uuid_t 
 */
constexpr esp_bt_uuid_t uuid128be(const std::array<uint8_t,16> bare) {
    esp_bt_uuid_t lit = {
        .len = ESP_UUID_LEN_128,
        .uuid = {
            .uuid128 = { 0 },
        }
    };
    for (int i=0; i<ESP_UUID_LEN_128; i++) {
        lit.uuid.uuid128[i] = bare[ESP_UUID_LEN_128 -i - 1];
    }
    return lit;
}

esp_bt_uuid_t serviceUuid = {
        .len = ESP_UUID_LEN_128,
        .uuid = {
            .uuid128 = 
                { 0x6E, 0x40, 0x00, 0x01, 0xB5, 0xA3, 0xF3, 0x93, 0xE0, 0xA9, 0xE5, 0x0E, 0x24, 0xDC, 0xCA, 0x9E },
        }
};

BLECharacteristicConfig rxCharacteristicConfig = {
    .uuid = uuid128be(
        { 0x6E, 0x40, 0x00, 0x02, 0xB5, 0xA3, 0xF3, 0x93, 0xE0, 0xA9, 0xE5, 0x0E, 0x24, 0xDC, 0xCA, 0x9E }
    ),
    .permissions = ESP_GATT_PERM_READ | ESP_GATT_PERM_WRITE,
    .properties = ESP_GATT_CHAR_PROP_BIT_WRITE,
    .control = { .auto_rsp = ESP_GATT_RSP_BY_APP },
    .descriptorConfigs = { }
};

BLECharacteristicConfig txCharacteristicConfig = {
    .uuid = uuid128be(        
            { 0x6E, 0x40, 0x00, 0x03, 0xB5, 0xA3, 0xF3, 0x93, 0xE0, 0xA9, 0xE5, 0x0E, 0x24, 0xDC, 0xCA, 0x9E }
    ),
    .permissions = ESP_GATT_PERM_READ | ESP_GATT_PERM_WRITE,
    .properties = ESP_GATT_CHAR_PROP_BIT_READ | ESP_GATT_CHAR_PROP_BIT_WRITE | ESP_GATT_CHAR_PROP_BIT_NOTIFY,
    .control = { .auto_rsp = ESP_GATT_AUTO_RSP },
    .descriptorConfigs = {{
        .uuid = UUID16(0x2902),
        .permissions = ESP_GATT_PERM_READ | ESP_GATT_PERM_WRITE,
        .control = { .auto_rsp = ESP_GATT_RSP_BY_APP }
    }}
};

BLEDescriptorConfig txNotifyDescriptorConfig = {
        .uuid = UUID16(0x2902),
        .permissions = ESP_GATT_PERM_READ | ESP_GATT_PERM_WRITE,
        .control = { .auto_rsp = ESP_GATT_AUTO_RSP }
};


UartService::UartService() :
    BLEService(serviceUuid),
    rxCharacteristic(this, rxCharacteristicConfig),
    txCharacteristic(this, txCharacteristicConfig),
    txNotifyDescriptor(this, txNotifyDescriptorConfig) {

    rxQueue = xQueueCreate(10, sizeof(char));
    txQueue = xQueueCreate(10, sizeof(char));

    txCharacteristic.setReadCallback([] (uint16_t *len, uint8_t **value) {
        ESP_LOGI(XTAG, "read");
        *len = 1;
        **value = 'F';
    });
    rxCharacteristic.setWriteCallback([this] (uint16_t len, uint8_t *value) {
        if (len > 0) {
            // maybe use std:string
            char *s = (char*)malloc(len + 1);
            if (s == 0) {
                ESP_LOGW(XTAG, "write: no memory");
                return;
            }
            std::memcpy(s, value, len);
            s[len] = 0;
            ESP_LOGI(XTAG, "write: '%s'", s);
            free(s);

            if (rxQueue) {
                const TickType_t timeToWait = 10;
                BaseType_t res = pdPASS;
                for (int i=0; i<len; i++) {
                    res = ::xQueueGenericSend(rxQueue, (void*) &value[i], timeToWait, queueSEND_TO_BACK);
                }
                if (res != pdPASS) {
                    ESP_LOGW(XTAG, "failed to enqueue");
                }
            }

        } else {
            ESP_LOGI(XTAG, "write empty");
        }
    });
}

void UartService::onConnect() {
    ESP_LOGI(XTAG, "starting echo notify task");
    ::xTaskCreate(echoTask, "echo", 4096, this, tskIDLE_PRIORITY, &taskHandle);
}

void UartService::onDisconnect() {
    if (taskHandle != NULL) {
        ESP_LOGI(XTAG, "stopping echo notify task");
        vTaskDelete(taskHandle);
        taskHandle = NULL;
    }
}

void UartService::echoTask(void *parameters) {
    QueueHandle_t &rxQueue = ((UartService*)parameters)->rxQueue;
    BLECharacteristic &txNotifyDescriptor = ((UartService*)parameters)->txCharacteristic;
if (rxQueue) {}

    ESP_LOGI(XTAG, "echo task started");
    while(1) {
        uint8_t c;
        const TickType_t timeToWait = 10;
        BaseType_t res;

        res = ::xQueueReceive(rxQueue, &c, timeToWait);
        if (res == pdTRUE) {

            ESP_LOGD(XTAG, "descriptor %0x", (unsigned int)&txNotifyDescriptor);
            ESP_LOGD(XTAG, "service %0x", (unsigned int)txNotifyDescriptor.getService());

            esp_gatt_if_t gatt_if = txNotifyDescriptor.getService()->getGattIf();
            uint16_t conn_id = txNotifyDescriptor.getService()->getConnId();
            uint16_t handle = txNotifyDescriptor.getHandle();

            ESP_LOGD(XTAG, "gatt_if: %0x conn_id %0x handle %0x", gatt_if, conn_id, handle);

            bool need_confirm = false;
            esp_err_t esp_err;

            esp_err = ::esp_ble_gatts_set_attr_value(handle, 1, &c);
            if (esp_err != ESP_OK) {
                ESP_LOGE(XTAG, "battery characteristic: set attribute: err: %0x", esp_err);
                return;
            }

            esp_err = ::esp_ble_gatts_send_indicate(gatt_if, conn_id, handle, 1, &c, need_confirm);
            if (esp_err != ESP_OK) {
                ESP_LOGE(XTAG, "notify: err: %0x", esp_err);
                return;
            }
        }
    }
}