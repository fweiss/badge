#pragma once

#include "player/Display.h"
#include "player/AnimationProgram.h"
#include "animations/PaintPixel.h"

#include "blewiz/BLECharacteristic.h"

#include "freertos/task.h"

class BadgeService : public BLEService {
public:
    BadgeService(Display &display, AnimationProgram &animationProgram);
    virtual ~BadgeService();

    void init();
    void setPaintPixel(PaintPixel *paintPixel) { this->paintPixel = paintPixel; }

    void onStarted() override;
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
    BLEDescriptor programIndexDescriptor;
    BLECharacteristic downloadCharacteristic;
    BLECharacteristic paintPixelCharacteristic;
    BLECharacteristic paintFrameCharacteristic;
    BLECharacteristic appVersionCharacteristic;
    BLECharacteristic frameDumpCharacteristic;

    static void batteryTask(void *parameters);
    TaskHandle_t batteryTaskHandle;

    void notifyCurrentProgram();

    std::vector<uint8_t> paintFrame;
};
