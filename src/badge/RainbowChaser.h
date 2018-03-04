#ifndef RAINBOW_CHASER_H
#define RAINBOW_CHASER_H

#include <deque>
#include <algorithm>

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
	hue += 25;
	int hue3 = hue * 3;
	// triangular wave
	int r = std::max(0, std::abs(256 + 128 - hue3) - 128);
	int g = std::max(0, 256 - std::abs(256 - hue3));
	int b = std::max(0, 256 - std::abs(256 + 256 - hue3));
	uint8_t attenuate = 15;
	// note blue value bump
	return Adafruit_NeoPixel::Color(r/attenuate, g/attenuate, b/7);
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
