#pragma once

#include <vector>

#include "PixelAnimation.h"
#include "RainbowChaser.h"
#include "CandyChaser.h"
#include <Adafruit_Neomatrix.h>

class StarburstAnimation : public PixelAnimation {
public:
	StarburstAnimation(Adafruit_NeoMatrix &matrix);
protected:
	virtual void drawFrame(unsigned long frameIndex) override;
private:
	static std::vector<std::vector<uint16_t>> paths;
	RainbowChaser chaser;
	std::vector<Chaser*> chasers;
};

StarburstAnimation::StarburstAnimation(Adafruit_NeoMatrix &matrix) : PixelAnimation(matrix), chaser(4) {
	setPeriod(180);

	for (uint16_t i=0; i<paths.size(); i++) {
		RainbowChaser *c = new RainbowChaser(4);
		c->setSpeed(12);
		c->preroll((i - 7) * ( i + 3));
		chasers.push_back(c);
	}
}

// in to out, clockwise from NW
std::vector<std::vector<uint16_t>> StarburstAnimation::paths = {
		{ 27, 18, 9, 0 },
		{ 19, 10, 1 },
		{ 11, 2 },
		{ 3 },
		{ 4 },
		{ 12, 5 },
		{ 20, 13, 6 },

		{ 28, 21, 14, 7 },
		{ 29, 22, 15 },
		{ 30, 23 },
		{ 31 },
		{ 39 },
		{ 38, 47 },
		{ 37, 46, 55 },

		{ 36, 45, 54, 63 },
		{ 44, 53, 62 },
		{ 52, 61 },
		{ 60 },
		{ 59 },
		{ 51, 58 },
		{ 43, 50, 57 },

		{ 35, 42, 49, 56 },
		{ 34, 41, 48 },
		{ 33, 40 },
		{ 32 },
		{ 24 },
		{ 25, 16 },
		{ 26, 17, 8 }
};

void StarburstAnimation::drawFrame(unsigned long frameIndex) {
	(void)frameIndex;

	uint16_t chaserIndex = 0;
	for (std::vector<uint16_t> path : paths) {
		Chaser* c = chasers.at(chaserIndex++);
		c->roll();
		drawPath(path, c);
	}
	matrix.show();
}
