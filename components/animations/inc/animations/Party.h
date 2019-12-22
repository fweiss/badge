#pragma once

#include "BitmapAnimation.h"

class Party : public BitmapAnimation {
public:
    Party(Display &display);
protected:
    static Frames frames;
};
