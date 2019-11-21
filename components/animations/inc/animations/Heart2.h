#pragma once

#include "BitmapAnimation.h"

#include <vector>

class Heart2 : public BitmapAnimation {
public:
    Heart2(Display &display);
protected:
    void drawFrame() override;
    void drawFrame(uint16_t frameIndex);

    static std::vector<std::vector<uint32_t>> heart;
};
