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

    txCharacteristic.setReadCallback([] (uint16_t *len, uint8_t **value) {
        ESP_LOGI(XTAG, "read");
        *len = 1;
        **value = 'F';
    });
    rxCharacteristic.setWriteCallback([] (uint16_t len, uint8_t *value) {
        if (len > 0) {
            char *s = (char*)malloc(len + 1);
            if (s == 0) {
                ESP_LOGW(XTAG, "write: no memory");
                return;
            }
            std::memcpy(s, value, len);
            s[len] = 0;
            ESP_LOGI(XTAG, "write: '%s'", s);
            free(s);
        } else {
            ESP_LOGI(XTAG, "write empty");
        }
    });
}

UartService::~UartService() {

}