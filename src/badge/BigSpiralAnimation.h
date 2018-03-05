#pragma once

#include <vector>

#include "Chaser.h"*
#include "RainbowChaser.h"
#include "PixelAnimation.h"

class BigSpiralAnimation : public PixelAnimation {
public:
	BigSpiralAnimation(Adafruit_NeoMatrix &matrix);
	static std::vector<std::vector<uint16_t>> paths;
	virtual void drawFrame(unsigned long frameIndex) override;
	virtual void drawPath(std::vector<uint16_t> path, Chaser *chaser);
protected:
private:
	RainbowChaser chaser;
};

std::vector<std::vector<uint16_t>> BigSpiralAnimation::paths = {
	{   0, 1, 2, 3, 4, 5, 6, 7, 15, 23, 31, 39, 47, 55, 63, 62, 61, 60, 59, 58, 57, 56, 48, 40, 32, 24, 16,
		8, 9, 10, 11, 12, 13, 14, 22, 30, 38, 46, 54, 53, 52, 51, 50, 49, 41, 33, 25, 17,
		18, 19, 20, 21, 29, 37, 45, 44, 43, 42, 34, 26,
		27, 28, 36, 35 }
};

BigSpiralAnimation::BigSpiralAnimation(Adafruit_NeoMatrix &matrix) : PixelAnimation(matrix), chaser(64) {
	setPeriod(40);
	setRepeatCount(20000);
	this->chaser.setReverse(true);
}

void BigSpiralAnimation::drawFrame(unsigned long frameIndex) {
	(void)frameIndex;

	chaser.roll();
	for (std::vector<uint16_t> path :paths) {
		drawPath(path, &chaser);
	}
    matrix.show();
}

void BigSpiralAnimation::drawPath(std::vector<uint16_t> spiral, Chaser *generator) {
	generator->roll();
	uint16_t i = 0;
	for(int pixelIndex : spiral) {
		uint32_t pixelColor = generator->get(i++);
		matrix.setPixelColor(pixelIndex, pixelColor);
	}
}
