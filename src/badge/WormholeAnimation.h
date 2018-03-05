#ifndef WORMHOLE_ANIMATION_H
#define WORMHOLE_ANIMATION_H

#include "BitmapAnimation.h"
#include "RainbowChaser.h"
#include <vector>

class WormholeAnimation : public PixelAnimation {
private:
    void drawPath(std::vector<uint16_t> pixels, uint32_t pixelColor);
    RainbowChaser rainbowChaser;
protected:
    void drawFrame(unsigned long frameIndex) override;
public:
    WormholeAnimation(Adafruit_NeoMatrix &matrix);
    static std::vector<std::vector<uint16_t>> paths;
};

WormholeAnimation::WormholeAnimation(Adafruit_NeoMatrix &matrix)  : PixelAnimation(matrix), rainbowChaser(4) {
    setRepeatCount(1);
    setPeriod(40);
    setFrameCount(1024);
    rainbowChaser.setReverse(true);
}

std::vector<std::vector<uint16_t>> WormholeAnimation::paths = {
		{ 0, 1, 2, 3, 4, 5, 6, 7, 15, 23, 31, 39, 47, 55, 63, 62, 61, 60, 59, 58, 57, 56, 48, 40, 32, 24, 16, 8 },
		{ 9, 10, 11, 12, 13, 14, 22, 30, 38, 46, 54, 53, 52, 51, 50, 49, 41, 33, 25, 17 },
		{ 18, 19, 20, 21, 29, 37, 45, 44, 43, 42, 34, 26 },
		{ 27, 28, 36, 35 }
};

void WormholeAnimation::drawFrame(unsigned long frameIndex) {
	(void)frameIndex;

	rainbowChaser.roll();
	uint16_t chaserIndex = 0;
	for (std::vector<uint16_t> path : paths) {
		drawPath(path, rainbowChaser.get(chaserIndex++));
	}
    matrix.show();
}

void WormholeAnimation::drawPath(std::vector<uint16_t> spiral, uint32_t pixelColor) {
	for(int pixelIndex : spiral) {
		matrix.setPixelColor(pixelIndex, pixelColor);
	}
}

#endif WORMHOLE_ANIMATION_H
