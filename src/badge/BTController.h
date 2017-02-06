#ifndef BT_CONTROLLER_H
#define BT_CONTROLLER_H

#include "AnimationSequence.h"
#include "SplashAnimation.h"
#include <SPI.h>
#include "Adafruit_BLE.h"
#include <Adafruit_BluefruitLE_SPI.h>
#include "Adafruit_BluefruitLE_UART.h"

extern SplashAnimation splash;

#define BLUEFRUIT_SPI_CS    8
#define BLUEFRUIT_SPI_IRQ   7
#define BLUEFRUIT_SPI_RST   4

#define VERBOSE_MODE        false

class BTController : public AnimationSequence {
private:
    Adafruit_BluefruitLE_SPI ble;
    boolean connected = false;
    boolean bannerWasSent = false;
    void handleClient(unsigned long now);
    void handleClientData();
    void handleClientCommandLine();
    void handleClientCommand();
    String commandLine;
    static String bannerText;
    static String helpText;
    static String errorText;
protected:
    boolean parseColor(uint8_t*, uint8_t*, uint8_t*);
public:
    BTController(unsigned long period) : AnimationSequence(period), ble(BLUEFRUIT_SPI_CS, BLUEFRUIT_SPI_IRQ, BLUEFRUIT_SPI_RST) {
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

        splash.start();
    }
    void update(unsigned long now) {
        handleClient(now);
        if (connected) {
            AnimationSequence::update(now);
        } else {
            splash.update(now);
        }
    }
};

void BTController::handleClient(unsigned long now) {
    if (! ble.isConnected()) {
        ble.end();
        connected = false;
        splash.start();
    } else if (connected) {
        // this cannot be done in setup
        if (! bannerWasSent) {
            ble.print(bannerText);
            bannerWasSent = true;
        }
        handleClientData();
    } else {
        if (ble.isConnected()) {
            delay(500); // some delay needed to make banner print at next event
            connected = true;
            commandLine = String("");
            bannerWasSent = false;
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
    if (commandLine[1] == '$') {
        float measuredvbat = analogRead(9);
        measuredvbat *= 2;    // we divided by 2, so multiply back
        measuredvbat *= 3.3;  // Multiply by 3.3V, our reference voltage
        measuredvbat /= 1024; // convert to voltage
        ble.print(measuredvbat);
        ble.print(" V\n");
        return;
    }
    int featureIndex = isDigit(commandLine[1]) ? commandLine.substring(1).toInt() : -1;
    if (featureIndex < 0 || featureIndex >= animationsSize) {
        ble.print(errorText);
        return;
    }
    Animation *animation = animations[featureIndex];
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
            uint8_t r;
            uint8_t g;
            uint8_t b;
            if (parseColor(&r, &g, &b)) {
                ticker.setTextColor(r, g, b);
            } else {
                ble.print(errorText);
            }
        }
    } else {
        if (subCommand == '+') {
            animation->start();
        }
        if (subCommand == '-') {
            animation->stop();
        }
    }
}

boolean BTController::parseColor(uint8_t* r, uint8_t* g, uint8_t* b) {
    char colorCode = commandLine[3];
    if (colorCode == 'r') {
        *r = 120;
        *g = 0;
        *b = 0;
        return true;
    }
    if (colorCode == 'g') {
        *r = 0;
        *g = 120;
        *b = 0;
        return true;
    }
    if (colorCode == 'b') {
        *r = 0;
        *g = 0;
        *b = 120;
        return true;
    }
    if (colorCode == 'y') {
        *r = 60;
        *g = 60;
        *b = 0;
        return true;
    }
    if (colorCode == 'w') {
        *r = 40;
        *g = 40;
        *b = 40;
        return true;
    }
    return false;
}

String BTController::bannerText = "badge v0.4.1\nenter \"?\" for help\n";

String BTController::errorText = "syntax error\nenter \"?\" for help\n";

String BTController::helpText = "\
enter a text line or a command line\n\
command line starts with \"!\"\n\
!n+ turn on feature \"n\"\n\
!n- turn off feature \"n\"\n\
!n#color change color\n\
!$ battery voltage\n\
features:\n\
 0 text\n\
 1 stack\n\
 2 plasma\n\
 3 squares\n\
 4 face\n\
 5 sacred\n\
";

#endif BT_CONTROLLER_H
