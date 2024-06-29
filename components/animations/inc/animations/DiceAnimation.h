#pragma once

#include "BitmapAnimation.h"

class DiceAnimation : public BitmapAnimation {
public:
    DiceAnimation();
private:
    static std::vector<std::vector<uint32_t>> frames;
};
