#pragma once

#include "BitmapAnimation.h"

class JsonAnimation : public BitmapAnimation {
public:
    JsonAnimation(Display &display);
    JsonAnimation(Display &display, const char *json);
    void loadJson(const char *json);
};
