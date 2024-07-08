#pragma once

#include <map>
#include "IndexedColorAnimation.h"

class DiceAnimation : public IndexedColorAnimation {
public:
    DiceAnimation();
    virtual ~DiceAnimation() {};

    virtual void drawFrame(Frame &frame) override;

    enum ColorIndex : uint8_t {
        black,
        white,
    };
    static std::map<ColorIndex,uint32_t> colorMap;
    static ColorIndex pixelIndexes[6][64];
};
