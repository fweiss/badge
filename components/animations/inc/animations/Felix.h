#pragma once

#include "IndexedColorAnimation.h"

class Felix : public IndexedColorAnimation {
public:
    Felix();

    enum  ColorIndex : uint8_t {
        back,
        fur,
        eye,
        tounge,
        paw
    };
    static std::map<ColorIndex, uint32_t> colorMap;
    static ColorIndex pixelIndexes[1][64];

    virtual void drawFrame(Frame &frame) override;
};
