#include "PathAnimation.h"

PathAnimation::PathAnimation(Display &display) : Animation(display) {

}

void PathAnimation::drawFrame() {
	for (ChaserPath cp : chaserPaths) {
	    cp.chaser->roll();
		drawPath(cp.path, cp.chaser);
	}
    display.show();
}

void PathAnimation::drawPath(std::vector<uint16_t> spiral, Chaser *chaser) {
//	chaser->roll();
	uint16_t i = 0;
	for (int pixelIndex : spiral) {
		uint32_t pixelColor = chaser->get(i++);
		display.setPixel(pixelIndex, pixelColor);
	}
}
