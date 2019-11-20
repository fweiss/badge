#pragma once

#include "Animation.h"

class Heart1 : public Animation {
public:
    Heart1(Display &display);
    virtual ~Heart1() {}
protected:
    void drawFrame() override;
    void drawFrame(uint32_t frameNumber);

    static uint8_t red[64][8];
    static uint8_t green[64][8];
    static uint8_t blue[64][8];

    uint16_t frameIndex;
};
