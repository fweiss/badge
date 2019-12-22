#pragma once

#include "BitmapAnimation.h"

class DiceAnimation : public BitmapAnimation {
public:
    DiceAnimation(Display &display);
private:
    static std::vector<std::vector<uint32_t>> frames;
};
