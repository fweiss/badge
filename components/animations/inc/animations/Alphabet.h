#pragma once

#include <map>
#include <vector>

#include "IndexedColorAnimation.h"

class Alphabet : public IndexedColorAnimation {
public:
    Alphabet();

    virtual void drawFrame(Frame &frame) override;

    enum ColorIndex: uint8_t {
        back,
        fore,
    };
    static std::map<ColorIndex, uint32_t> colorMap;
    static ColorIndex pixelIndexes[52][64];
};
