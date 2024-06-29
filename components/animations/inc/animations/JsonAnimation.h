#pragma once

#include "BitmapAnimation.h"

class JsonAnimation : public BitmapAnimation {
public:
    JsonAnimation();
    JsonAnimation(const char *json);
    void loadJson(const char *json);
};
