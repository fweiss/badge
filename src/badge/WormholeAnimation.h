#ifndef WORMHOLE_ANIMATION_H
#define WORMHOLE_ANIMATION_H

#include "BitmapAnimation.h"
#include "ChaseGenerator.h"
#include "RainbowChaser.h"
// following to fix Arduino.h when using stdlib
#undef max
#undef min
#include <vector>
#include <led_sysdefs.h>
#include <pixeltypes.h>

class WormholeAnimation : public PixelAnimation {
private:
    void drawPath(std::vector<int> pixels, uint32_t pixelColor);
    RainbowChaser rainbowChaser;
protected:
    void drawFrame(unsigned long frameIndex) override;
public:
    WormholeAnimation(Adafruit_NeoMatrix &matrix) : PixelAnimation(matrix), rainbowChaser(4) {
        setRepeatCount(1);
        setPeriod(240);
        setFrameCount(1024);
    }
};

void WormholeAnimation::drawFrame(unsigned long frameIndex) {
	static const std::vector<int> spiral0 = {0, 1, 2, 3, 4, 5, 6, 7, 15, 23, 31, 39, 47, 55, 63, 62, 61, 60, 59, 58, 57, 56, 48, 40, 32, 24, 16, 8};
	static const std::vector<int> spiral1 = {9, 10, 11, 12, 13, 14, 22, 30, 38, 46, 54, 53, 52, 51, 50, 49, 41, 33, 25, 17 };
	static const std::vector<int> spiral2 = {18, 19, 20, 21, 29, 37, 45, 44, 43, 42, 34, 26 };
	static const std::vector<int> spiral3 = { 27, 28, 36, 35 };

	rainbowChaser.roll();
	drawPath(spiral0, rainbowChaser.get(3));
	drawPath(spiral1, rainbowChaser.get(2));
	drawPath(spiral2, rainbowChaser.get(1));
	drawPath(spiral3, rainbowChaser.get(0));
    matrix.show();
}

void WormholeAnimation::drawPath(std::vector<int> spiral, uint32_t pixelColor) {
	for(int pixelIndex : spiral) {
		matrix.setPixelColor(pixelIndex, pixelColor);
	}
}

#endif WORMHOLE_ANIMATION_H
