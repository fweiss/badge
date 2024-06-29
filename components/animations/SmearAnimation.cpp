#include "SmearAnimation.h"

SmearAnimation::SmearAnimation() : Animation() {
    r = 0;
}

void SmearAnimation::drawFrame(Frame &frame) {
    uint16_t triangle = (r > 255) ? (511 -r) : r;
    for (int x=0; x<8; x++) {
        for (int y=0; y<8; y++) {
            uint16_t  p = y * 8 + x;
            uint8_t g = 20 + 15 * y;
            uint8_t b = 20 + 13 * x;
            // frame.setPixelRgb(p, triangle, g, b);
            frame.setPixel(p, triangle, g, b);

        }
    }
	r = (r + 3) % 512;
}
