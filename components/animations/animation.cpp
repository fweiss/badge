#include "animation.h"

Animation::Animation(led_strip_t *ledStrip) : Animation(new Display(ledStrip)) {
//	this(new Display(ledStrip))
	this->ledStrip = ledStrip;
	r = 0;
}

Animation::Animation(Display *display) {
	this->display = display;
	r = 0;
}

void Animation::drawFrame() {
//    ESP_LOGI("ANIMATION", "Animation::drawFrame\n");
	for (int x=0; x<8; x++) {
		for (int y=0; y<8; y++) {
			uint16_t  p = y * 8 + x;
			uint8_t g = 20 + 5 * y;
			uint8_t b = 20 + 3 * x;
//			led_strip_set_pixel_rgb(ledStrip, p, r / 12, g / 12, b / 12);
			display->setPixelRgb(p, r, g, b);
		}
	}
//	led_strip_set_pixel_rgb(ledStrip, 0, r, 20, 20);
//	led_strip_set_pixel_rgb(ledStrip, 4, 20, r, 20);

//	led_strip_show(ledStrip);
	display->update();
	r = (r + 3) % 256;
}
