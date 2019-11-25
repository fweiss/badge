#pragma once

#include "BitmapAnimation.h"

#include <vector>

class HeartAnimation : public BitmapAnimation {
public:
    HeartAnimation(Display &display);
protected:

    static std::vector<std::vector<uint32_t>> heart;
};
