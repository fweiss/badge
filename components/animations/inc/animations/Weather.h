#pragma once

#include "BitmapAnimation.h"

class Weather : public BitmapAnimation {
public:
    Weather(Display &display);
protected:
    static Frames frames;
};
