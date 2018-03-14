#ifndef SPIRAL_ANIMATION_H
#define SPIRAL_ANIMATION_H

#include "BitmapAnimation.h"
#include "CandyChaser.h"
#include <vector>
#include "StdThrowHandlers.h"

class SpiralAnimation : public PixelAnimation {
private:
    CandyChaser* generator0;
    CandyChaser* generator1;
    CandyChaser* generator2;
    CandyChaser* generator3;
protected:
    void drawFrame(unsigned long frameIndex) override;
public:
    SpiralAnimation(Adafruit_NeoMatrix &matrix) : PixelAnimation(matrix) {
        setRepeatCount(80);
        setPeriod(40);
        setFrameCount(200);
        generator0 = new CandyChaser(0, 0, 0);
        generator1 = new CandyChaser(60, 10, 0);
        generator2 = new CandyChaser(120, 0, 10);
        generator3 = new CandyChaser(180, 10, 0);
    }
};

void SpiralAnimation::drawFrame(unsigned long frameIndex) {
	static const std::vector<uint16_t> spiral0 = {0, 1, 2, 3, 4, 5, 6, 14, 22, 30, 38, 46, 45, 44, 43, 35};
	static const std::vector<uint16_t> spiral1 = {7, 15, 23, 31, 39, 47, 55, 54, 53, 52, 51, 50, 42, 34, 26, 27};
	static const std::vector<uint16_t> spiral2 = {63, 62, 61, 60, 59, 58, 57, 49, 41, 33, 25, 17, 18, 19, 20, 28};
	static const std::vector<uint16_t> spiral3 = {56, 48, 40, 32, 24, 16, 8, 9, 10, 11, 12, 13, 21, 29, 37, 36};

	drawPath(spiral0, generator0);
	drawPath(spiral1, generator1);
	drawPath(spiral2, generator2);
	drawPath(spiral3, generator3);
    matrix.show();
}

#endif SPIRAL_ANIMATION_H
