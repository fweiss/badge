#pragma once

#include "Chaser.h"

class RainbowChaser : public Chaser {
public:
    RainbowChaser(uint16_t size, uint16_t step);

    uint32_t nextColor() override;
protected:
    int16_t hue;
};
