#pragma once

#include <algorithm>

#include "Chaser.h"

class RainbowChaser : public Chaser {
public:
	RainbowChaser(uint8_t size);
	virtual uint32_t nextColor() override;
	void setSpeed(uint8_t speed);
protected:
private:
	uint8_t hue;
	uint8_t speed;
};

RainbowChaser::RainbowChaser(uint8_t size) : Chaser(size) {
	this->hue = 0;
	speed = 13;
}

uint32_t RainbowChaser::nextColor() {
	hue += speed;
	int hue3 = hue * 3;
	// triangular wave
	int r = std::max(0, std::abs(256 + 128 - hue3) - 128);
	int g = std::max(0, 256 - std::abs(256 - hue3));
	int b = std::max(0, 256 - std::abs(256 + 256 - hue3));
	uint8_t attenuate = 35;
	// note blue value bump
	return Adafruit_NeoPixel::Color(r/attenuate, g/attenuate, b/7);
}

void RainbowChaser::setSpeed(uint8_t speed) {
	this->speed = speed;
}
