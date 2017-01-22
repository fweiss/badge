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
    boolean bannerWasSent = false;
    void handleClient(unsigned long now);
    void handleClientData();
    void handleClientCommand();
    String commandLine;
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
        handleClient(now);
        UberAnimation::update(now);
    }
};

void BTController::handleClient(unsigned long now) {
    if (connected) {
        // this cannot be done in setup
        if (! bannerWasSent) {
            ble.print("badge v0.0.1\n");
            bannerWasSent = true;
        }
        handleClientData();
    } else {
        if (ble.isConnected()) {
            delay(500); // some delay needed to make banner print at next event
            connected = true;
            commandLine = String("");
        }
   }
}

void BTController::handleClientData() {
    while (ble.available()) {
        int c = ble.read();
        if (c == 0x0A || c == 0x0D) {
            handleClientCommand();
            commandLine = String("");
        } else {
            commandLine += String((char)c);
        }
    }
//    ticker.setTextColor(120, 0, 0);
//    ble.print("hello");
}

void BTController::handleClientCommand() {
    int controlCommand = commandLine[0];
    if (controlCommand == '!') {
        ticker.setTextColor(120, 0, 0);
    } else {
        ticker.setText(commandLine);
    }
}

#endif BT_CONTROLLER
