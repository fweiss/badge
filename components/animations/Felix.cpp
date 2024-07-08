#include "Felix.h"

#include "esp_log.h"

// Felix::Felix() : IndexedColorAnimation(&zz, &pixelIndexes) {}
Felix::Felix() {
    IndexedColorAnimation::setFrameCount(pixelIndexes);
}

void Felix::drawFrame(Frame &frame) {
    IndexedColorAnimation::drawFrame(frame, colorMap, pixelIndexes);
}

std::map<Felix::ColorIndex, uint32_t> Felix::colorMap = {
    {ColorIndex::back, 0x000000},
    {ColorIndex::fur, 0xe8bc50},
    {ColorIndex::eye, 0x53befb},
    {ColorIndex::tounge, 0xff8080},
    {ColorIndex::paw, 0xffffff}
};

Felix::ColorIndex Felix::pixelIndexes[1][64]{
    {
        back, fur, back, back, fur, back, back, back,
        back, fur, fur, fur, fur, back, back, back,
        back, eye, fur, eye, fur, back, back, back,
        back, fur, fur, fur, fur, fur, back, back,
        back, back, tounge, fur, fur, fur, back, fur,
        back, back, back, fur, fur, fur, back, fur,
        back, back, back, fur, fur, fur, back, fur,
        back, back, back, paw, fur, paw, fur, back,
    }
};
