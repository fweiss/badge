#pragma once

#include <unordered_map>
#include <queue>

#include "freertos/FreeRTOS.h"

#include "esp_gatts_api.h"

#define UUID16(x) { .len = ESP_UUID_LEN_16, .uuid = { .uuid16 = (x) } }
#define UUID128(x) { .len = ESP_UUID_LEN_16, .uuid = { .uuid128 = x } }

#include "BLEAttribute.h"
//class BLEAttribute;
//class BLECharacteristic;
//class BLECharacteristicConfig;

//struct BLEUuid;
struct BLEUuid {
    size_t hash() {
        return 0;
    }
    bool operator==(BLEUuid&) {
        return 0;
    }
};

class BLEService : public BLEAttribute {
public:
    BLEService(const esp_bt_uuid_t &uuid);
    virtual ~BLEService() {}

    esp_gatt_if_t gatt_if;
    uint16_t conn_id;

    esp_gatt_if_t getGattIf() { return this->gatt_if; }
    uint16_t getConnId() { return this->conn_id; }
    uint16_t getHandle() { return serviceHandle; }

    // todo make friend
    void attach(BLEAttribute *attribute);
    void registerNextAttribute(uint16_t attr_handle);
    void addToService(BLEService &service) override;

    void handleGattsEvent(esp_gatts_cb_event_t event, esp_gatt_if_t gatts_if, esp_ble_gatts_cb_param_t *param);

    virtual void onStarted() {}
    virtual void onConnect() {}
    virtual void onDisconnect() {}

    static const uint16_t ATTR_MAX_LEN = 16;

protected:
    std::unordered_map<uint16_t, BLEAttribute*> characteristicByHandle;
    std::queue<BLEAttribute*> characteristicQueue;

private:
    uint16_t serviceHandle;

    void addCharacteristic(BLEAttribute *characteristic);
};
