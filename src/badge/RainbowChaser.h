#ifndef RAINBOW_CHASER_H
#define RAINBOW_CHASER_H

#include <deque>
#include <led_sysdefs.h>
#include <pixeltypes.h>

class RainbowChaser {
public:
	RainbowChaser(uint8_t size);
	uint32_t get(uint8_t index);
	void roll();
protected:
	std::deque<uint32_t> channels;
private:
	uint32_t nextColor();
	uint8_t hue;
};

RainbowChaser::RainbowChaser(uint8_t size) {
	for (int i=0; i<4; i++) {
		channels.push_front(nextColor());
	}
}
uint32_t RainbowChaser::nextColor() {
	hue += 12;
	CHSV hsv(hue, 255, 120);
	CRGB rgb;
	hsv2rgb_rainbow(hsv, rgb);
	return Adafruit_NeoPixel::Color(rgb.r, rgb.g, rgb.b);
}
uint32_t RainbowChaser::get(uint8_t index) {
	return channels.at(index);
}
void RainbowChaser::roll() {
	uint32_t nc = nextColor();
	if (false) {
		channels.pop_front();
		channels.push_back(nc);
	} else {
		channels.pop_back();
		channels.push_front(nc);
	}
}

#endif RAINBOW_CHASER_H