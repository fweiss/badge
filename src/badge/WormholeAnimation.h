#ifndef WORMHOLE_ANIMATION_H
#define WORMHOLE_ANIMATION_H

#include "BitmapAnimation.h"
#include "ChaseGenerator.h"
// following to fix Arduino.h when using stdlib
#undef max
#undef min
#include <vector>

class WormholeAnimation : public PixelAnimation {
private:
    void drawPath(std::vector<int> pixels, uint32_t pixelColor);
    ChaseGenerator* generator0;
    ChaseGenerator* generator1;
    ChaseGenerator* generator2;
    ChaseGenerator* generator3;
protected:
    void drawFrame(unsigned long frameIndex) override;
public:
    WormholeAnimation(Adafruit_NeoMatrix &matrix) : PixelAnimation(matrix) {
        setRepeatCount(80);
        setPeriod(440);
        generator0 = new ChaseGenerator(0, 0, 0);
        generator1 = new ChaseGenerator(60, 10, 0);
        generator2 = new ChaseGenerator(120, 0, 10);
        generator3 = new ChaseGenerator(180, 10, 0);
    }
};

void WormholeAnimation::drawFrame(unsigned long frameIndex) {
	static const std::vector<int> spiral0 = {0, 1, 2, 3, 4, 5, 6, 7, 15, 23, 31, 39, 47, 55, 63, 62, 61, 60, 59, 58, 57, 56, 48, 40, 32, 24, 16, 8};
	static const std::vector<int> spiral1 = {9, 10, 11, 12, 13, 14, 22, 30, 38, 46, 54, 53, 52, 51, 50, 49, 41, 33, 25, 17 };
	static const std::vector<int> spiral2 = {18, 19, 20, 21, 29, 37, 45, 44, 43, 42, 34, 26 };
	static const std::vector<int> spiral3 = { 27, 28, 36, 35 };

	generator0->roll();
	drawPath(spiral0, generator0->get(3));
	drawPath(spiral1, generator0->get(2));
	drawPath(spiral2, generator0->get(1));
	drawPath(spiral3, generator0->get(0));
    matrix.show();
}

void WormholeAnimation::drawPath(std::vector<int> spiral, uint32_t pixelColor) {
	for(int pixelIndex : spiral) {
		matrix.setPixelColor(pixelIndex, pixelColor);
	}
}

#endif WORMHOLE_ANIMATION_H
