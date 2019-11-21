#pragma once

#include "BitmapAnimation.h"

class Felix : public BitmapAnimation {
public:
    Felix(Display &display);
protected:
    static std::vector<std::vector<uint32_t>> yy;
};
