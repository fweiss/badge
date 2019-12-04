#pragma once

#include "BitmapAnimation.h"

class Checkerboard : public BitmapAnimation {
public:
    Checkerboard(Display &display);
protected:
    static std::vector<std::vector<uint32_t>> frames;
};
