#pragma once

#include "BitmapAnimation.h"

class EmojiAnimation : public BitmapAnimation {
public:
    EmojiAnimation();
private:
    static std::vector<std::vector<uint32_t>> frames;
};
