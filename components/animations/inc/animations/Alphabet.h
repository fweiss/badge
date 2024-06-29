#pragma once

#include "BitmapAnimation.h"

class Alphabet : public BitmapAnimation {
public:
    Alphabet();
private:
    static BitmapAnimation::Frames frames;
};
