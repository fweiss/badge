#pragma once

#include "animations/display.h"
#include "animations/AnimationProgram.h"
#include "animations/PaintPixel.h"

#include "blewiz/BLECharacteristic.h"

#include "freertos/task.h"

class BadgeService : public BLEService {
public:
    BadgeService(Display &display, AnimationProgram &animationProgram);
    virtual ~BadgeService();

    void init();
    void setPaintPixel(PaintPixel *paintPixel) { this->paintPixel = paintPixel; }

    void onConnect() override;
    void onDisconnect() override;

private:
    Display &display;
    AnimationProgram &animationProgram;
    PaintPixel *paintPixel;


    BLECharacteristic batteryCharacteristic;
    BLEDescriptor batteryNotifyDesciptor;
    BLECharacteristic brightnessCharacteristic;
    BLECharacteristic programCharacteristic;
    BLECharacteristic downloadCharacteristic;
    BLECharacteristic paintPixelCharacteristic;
    BLECharacteristic paintFrameCharacteristic;

    static void batteryTask(void *parameters);
    TaskHandle_t taskHandle;
};
