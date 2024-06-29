#include "Animation.h"

static const uint16_t defaultFramePeriodMillis = 30;

Animation::Animation() : framePeriodMillis(defaultFramePeriodMillis) {
}

// move to Display
const std::vector<uint32_t> *Animation::frameDump() const {
    static std::vector<uint32_t>frame;
    // frame.clear();
    // for (int i=0; i<64; i++) {
    //     const uint32_t color = display.getPixel(i);
    //     frame.push_back(color);
    // }
    return &frame;
}
