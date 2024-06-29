#pragma once

#include "BitmapAnimation.h"

class SpinBottle2 : public BitmapAnimation {
public:
    SpinBottle2();
protected:
    static std::vector<std::vector<uint32_t>> frames;
};
