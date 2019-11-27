#pragma once

#include "BitmapAnimation.h"

class SpinBottleAnimation : public BitmapAnimation {
public:
    SpinBottleAnimation(Display &display);
private:
    static std::vector<std::vector<uint32_t>> frames;

};
