#pragma once

#include "PathAnimation.h"
#include "CandyChaser.h"
#include <vector>

class SpiralAnimation : PathAnimation {
private:
    CandyChaser* generator0;
    CandyChaser* generator1;
    CandyChaser* generator2;
    CandyChaser* generator3;
	static const std::vector<uint16_t> spiral0;
	static const std::vector<uint16_t> spiral1;
	static const std::vector<uint16_t> spiral2;
	static const std::vector<uint16_t> spiral3;

protected:
    void drawPath(std::vector<uint16_t> spiral, Chaser *chaser);
public:
    SpiralAnimation(Display &display);
    void drawFrame(); // todo move to base class
};
