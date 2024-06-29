#pragma once

#include "BitmapAnimation.h"

class SpinBottleAnimation : public BitmapAnimation {
public:
    SpinBottleAnimation();
private:
    static std::vector<std::vector<uint32_t>> frames;

};
