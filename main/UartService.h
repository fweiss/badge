#pragma once

#include "blewiz/BLEService.h"
#include "blewiz/BLECharacteristic.h"
#include <freertos/queue.h>

class UartService: public BLEService  {
public:
    // static constexpr char *  SERVICE_UUID = "6E400001-B5A3-F393-E0A9-E50E24DCCA9E";
    // static constexpr char *  CHARACTERISTIC_UUID_RX = "6E400002-B5A3-F393-E0A9-E50E24DCCA9E";
    // static constexpr char *  CHARACTERISTIC_UUID_TX = "6E400003-B5A3-F393-E0A9-E50E24DCCA9E";

    static constexpr uint8_t SERVICE_UUID[16] =
        { 0x6E, 0x40, 0x00, 0x01, 0xB5, 0xA3, 0xF3, 0x93, 0xE0, 0xA9, 0xE5, 0x0E, 0x24, 0xDC, 0xCA, 0x9E };
    static constexpr uint8_t CHARACTERISTIC_UUID_RX[16] =
        { 0x6E, 0x40, 0x00, 0x02, 0xB5, 0xA3, 0xF3, 0x93, 0xE0, 0xA9, 0xE5, 0x0E, 0x24, 0xDC, 0xCA, 0x9E };
    static constexpr uint8_t CHARACTERISTIC_UUID_TX[16] =
        { 0x6E, 0x40, 0x00, 0x03, 0xB5, 0xA3, 0xF3, 0x93, 0xE0, 0xA9, 0xE5, 0x0E, 0x24, 0xDC, 0xCA, 0x9E };

    UartService();
    virtual ~UartService() { }

    BLECharacteristic rxCharacteristic;
    BLECharacteristic txCharacteristic;
    BLEDescriptor txNotifyDescriptor;

    void onConnect() override;
    void onDisconnect() override;

    QueueHandle_t rxQueue;
    QueueHandle_t txQueue;
    static void echoTask(void *parameters);
    TaskHandle_t taskHandle;
};
