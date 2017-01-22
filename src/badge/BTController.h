#ifndef BT_BTController
#define BT_CONTROLLER

#include "UberAnimation.h"
#include <SPI.h>
#include "Adafruit_BLE.h"
#include <Adafruit_BluefruitLE_SPI.h>
#include "Adafruit_BluefruitLE_UART.h"

#define BLUEFRUIT_SPI_CS    8
#define BLUEFRUIT_SPI_IRQ   7
#define BLUEFRUIT_SPI_RST   4

#define VERBOSE_MODE        false

class BTController : public UberAnimation {
private:
    Adafruit_BluefruitLE_SPI ble;
    boolean connected = false;
    void handleClient();
protected:
public:
    BTController(unsigned long period) : UberAnimation(period), ble(BLUEFRUIT_SPI_CS, BLUEFRUIT_SPI_IRQ, BLUEFRUIT_SPI_RST) {
    }
    void setup() {
        ble.begin(VERBOSE_MODE);
        ble.factoryReset();
        ble.echo(false);
        ble.info();
        ble.verbose(false);
        ble.setMode(BLUEFRUIT_MODE_DATA);

        ticker.start();
        stack.stop();
        plasma.stop();
        pixel.stop();
        face.stop();
        sacred.stop();
    }
    void update(unsigned long now) {
        handleClient();
        UberAnimation::update(now);
    }
};

void BTController::handleClient() {
    if (connected) {
        if (ble.available()) {
            int c = ble.read();
            ticker.setTextColor(120, 0, 0);
            ble.print("hello");
        }
    } else {
        if (ble.isConnected()) {
            connected = true;
//                ble.print("badge v0.0.1\n");
        }
    }
}

#endif BT_CONTROLLER
