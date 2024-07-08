#pragma once

#include <map>

#include "IndexedColorAnimation.h"

class EmojiAnimation : public IndexedColorAnimation {
public:
    EmojiAnimation();
    virtual ~EmojiAnimation() {};

    void drawFrame(Frame& frame) override;

    enum ColorIndex : uint8_t {
        back,
        fore,
        tear,
        anger,
        tongue
    };
    static std::map<ColorIndex,uint32_t> colorMap;
    static ColorIndex pixelIndexes[12][64];
};
