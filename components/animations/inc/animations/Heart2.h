#pragma once

#include "BitmapAnimation.h"

#include <vector>

class Heart2 : public BitmapAnimation {
public:
    Heart2(Display &display);
protected:

    static std::vector<std::vector<uint32_t>> heart;
};
