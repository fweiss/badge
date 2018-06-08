#include "SmearAnimation.h"

SmearAnimation::SmearAnimation(led_strip_t *ledStrip) : SmearAnimation(new Display(ledStrip)) {
	r = 0;
}

SmearAnimation::SmearAnimation(Display* display) : SmearAnimation() {
	this->display = display;
}

SmearAnimation::SmearAnimation() {
	r = 0;
}

void SmearAnimation::drawFrame() {
	for (int x=0; x<8; x++) {
		for (int y=0; y<8; y++) {
			uint16_t  p = y * 8 + x;
			uint8_t g = 20 + 15 * y;
			uint8_t b = 20 + 13 * x;
			display->setPixelRgb(p, r, g, b);
		}
	}
	display->update();
	r = (r + 3) % 256;
}
