#pragma once

#include "BitmapAnimation.h"

#include <vector>

class Heart2 : public BitmapAnimation {
public:
    Heart2(Display &display);
protected:
    void drawFrame() override;
    void drawFrame(uint16_t frameIndex);

    void nextFrame() { frameIndex = (frameIndex + 1) % bm.size(); }

    uint16_t frameIndex;

    std::vector<std::vector<uint32_t>> &bm;
    static std::vector<std::vector<uint32_t>> heart;
};
