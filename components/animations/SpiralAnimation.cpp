#include "SpiralAnimation.h"

SpiralAnimation::SpiralAnimation(Display &display) : PathAnimation(display) {
//        setRepeatCount(80);
//        setPeriod(40);
//        setFrameCount(200);
        generator0 = new CandyChaser(0, 0, 0);
        generator1 = new CandyChaser(60, 10, 0);
        generator2 = new CandyChaser(120, 0, 10);
        generator3 = new CandyChaser(180, 10, 0);

        chaserPaths = {
        		ChaserPath(new CandyChaser(0, 0, 0), {0, 1, 2, 3, 4, 5, 6, 14, 22, 30, 38, 46, 45, 44, 43, 35} ),
        		ChaserPath(new CandyChaser(60, 10, 00), {7, 15, 23, 31, 39, 47, 55, 54, 53, 52, 51, 50, 42, 34, 26, 27} ),
        		ChaserPath(new CandyChaser(120, 0, 10), {63, 62, 61, 60, 59, 58, 57, 49, 41, 33, 25, 17, 18, 19, 20, 28} ),
        		ChaserPath(new CandyChaser(180, 10, 0), {56, 48, 40, 32, 24, 16, 8, 9, 10, 11, 12, 13, 21, 29, 37, 36} )
        };
    }

const std::vector<uint16_t> SpiralAnimation::spiral0 = {0, 1, 2, 3, 4, 5, 6, 14, 22, 30, 38, 46, 45, 44, 43, 35};
const std::vector<uint16_t> SpiralAnimation::spiral1 = {7, 15, 23, 31, 39, 47, 55, 54, 53, 52, 51, 50, 42, 34, 26, 27};
const std::vector<uint16_t> SpiralAnimation::spiral2 = {63, 62, 61, 60, 59, 58, 57, 49, 41, 33, 25, 17, 18, 19, 20, 28};
const std::vector<uint16_t> SpiralAnimation::spiral3 = {56, 48, 40, 32, 24, 16, 8, 9, 10, 11, 12, 13, 21, 29, 37, 36};


void SpiralAnimation::drawFrame() {
//	drawPath(spiral0, generator0);
//	drawPath(spiral1, generator1);
//	drawPath(spiral2, generator2);
//	drawPath(spiral3, generator3);
	for (ChaserPath cp : chaserPaths) {
		drawPath(cp.path, cp.chaser);
	}
    display.show();
}
