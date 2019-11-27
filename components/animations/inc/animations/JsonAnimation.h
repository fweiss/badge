#pragma once

#include "BitmapAnimation.h"

class JsonAnimation : public BitmapAnimation {
public:
    JsonAnimation(Display &display);
    void loadJson();
};
