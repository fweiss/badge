#include "SmearAnimation.h"

SmearAnimation::SmearAnimation(Display &display) : Animation(display) {
    r = 0;
}

void SmearAnimation::drawFrame() {
    uint16_t triangle = (r > 255) ? (511 -r) : r;
	for (int x=0; x<8; x++) {
		for (int y=0; y<8; y++) {
			uint16_t  p = y * 8 + x;
			uint8_t g = 20 + 15 * y;
			uint8_t b = 20 + 13 * x;
			display.setPixelRgb(p, triangle, g, b);
		}
	}
	display.update();
	r = (r + 3) % 512;
}
