#pragma once

#include "BitmapAnimation.h"

class MiscellanyAnimation : public BitmapAnimation {
public:
    MiscellanyAnimation(Display &display);
protected:
    static Frames frames;
};
