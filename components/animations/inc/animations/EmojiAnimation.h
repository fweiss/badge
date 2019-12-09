#pragma once

#include "BitmapAnimation.h"

class EmojiAnimation : public BitmapAnimation {
public:
    EmojiAnimation(Display &);
private:
    static std::vector<std::vector<uint32_t>> frames;
};
