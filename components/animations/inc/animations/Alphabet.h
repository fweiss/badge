#pragma once

#include "BitmapAnimation.h"

class Alphabet : public BitmapAnimation {
public:
    Alphabet(Display &display);
private:
    static BitmapAnimation::Frames frames;
};
