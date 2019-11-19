#pragma once

#include "Animation.h"

class BitmapAnimation : public Animation {
public:
    BitmapAnimation(Display &display);

    static uint32_t bitmap[8][8];

protected:
    void drawFrame() override;
};
