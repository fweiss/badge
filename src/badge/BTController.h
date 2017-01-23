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
    void handleClientCommandLine();
    void handleClientCommand();
    String commandLine;
    static String helpText;
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
            handleClientCommandLine();
            commandLine = String("");
        } else {
            commandLine += String((char)c);
        }
    }
}

void BTController::handleClientCommandLine() {
    if (commandLine.length() == 0) {
        return;
    }
    int controlCommand = commandLine[0];
    if (controlCommand == '!') {
        handleClientCommand();
    } else if (controlCommand == '?') {
        ble.print(helpText);
    } else {
        ticker.setText(commandLine);
    }
}

void BTController::handleClientCommand() {
    int featureCode = commandLine[1];
    int subCommand = commandLine[2];
    if (featureCode == '0') {
        if (subCommand == '+') {
            ticker.start();
        }
        if (subCommand == '-') {
            ticker.stop();
        }
        if (subCommand == '#') {
            ticker.setTextColor(120, 0, 0);
        }
    }
    if (featureCode == '1') {
        if (subCommand == '+') {
            plasma.start();
        }
        if (subCommand == '-') {
            plasma.stop();
        }
    }
}

String BTController::helpText = "\
enter a text line or a command line\n\
command line starts with \"!\"\n\
!n+ turn on feature \"n\"\n\
!n- turn off feature \"n\"\n\
!n#hhhhhh change color\n\
features:\n\
 0 text\n\
 1 plasma\n\
";

#endif BT_CONTROLLER
