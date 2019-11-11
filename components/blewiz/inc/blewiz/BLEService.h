#pragma once

#include <unordered_map>
#include <queue>

#include "freertos/FreeRTOS.h"

#include "esp_gatts_api.h"

#define UUID16(x) { .len = ESP_UUID_LEN_16, .uuid = { .uuid16 = x } }

//#include "BLECharacteristic.h"
class BLEAttribute;
//class BLECharacteristic;
//class BLECharacteristicConfig;

// specialization for std::unordered_map
struct uuid_hash {
    size_t operator()(const esp_bt_uuid_t &uuid ) const {
        size_t hash;
        switch (uuid.len) {
        case ESP_UUID_LEN_16:
            return std::hash<unsigned short>{}((unsigned short)uuid.uuid.uuid16);
            break;
        case ESP_UUID_LEN_32:
            return std::hash<unsigned int>{}((unsigned int)uuid.uuid.uuid32);
            break;
        case ESP_UUID_LEN_128:
//            return std::hash<uint8_t*>{}(uuid.uuid.uuid128);
            hash = 0;
            return hash;
           break;
        default:
            return 0; //undefined
        }
    }
};

// specialization for std::unordered_map
struct uuid_equal {
    bool operator()(const esp_bt_uuid_t &lhs, const esp_bt_uuid_t &rhs) const {
        switch (lhs.len) {
        case ESP_UUID_LEN_16:
            return std::equal_to<unsigned short>{}((unsigned short)lhs.uuid.uuid16, (unsigned short)rhs.uuid.uuid16);
            break;
        case ESP_UUID_LEN_32:
            return std::equal_to<unsigned int>{}((unsigned int)lhs.uuid.uuid32, (unsigned int)rhs.uuid.uuid32);
            break;
        case ESP_UUID_LEN_128:
            return false;
            break;
        default:
            return false; //undefined
        }
    }
};

//struct BLEUuid;
struct BLEUuid {
    size_t hash() {
        return 0;
    }
    bool operator==(BLEUuid&) {
        return 0;
    }
};

class BLEService {
public:
    BLEService();
    virtual ~BLEService() {}

    // todo make friend
    void attach(BLEAttribute *attribute);

    void handleGattsEvent(esp_gatts_cb_event_t event, esp_gatt_if_t gatts_if, esp_ble_gatts_cb_param_t *param);

    static const uint16_t ATTR_MAX_LEN = 16;
    uint16_t getHandle() { return serviceHandle; }

protected:
    std::unordered_map<esp_bt_uuid_t, BLEAttribute*, uuid_hash, uuid_equal> characteristicByUuid;
    std::unordered_map<uint16_t, BLEAttribute*> characteristicByHandle;
    std::queue<BLEAttribute*> characteristicQueue;

private:
    uint16_t serviceHandle;

    void addCharacteristic(BLEAttribute *characteristic);
};
