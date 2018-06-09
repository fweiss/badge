#pragma once

#include "Animation.h"
#include "Chaser.h"
#include <vector>

class PathAnimation : public Animation {
private:
protected:
	void drawPath(std::vector<uint16_t> spiral, Chaser *chaser);
public:
	PathAnimation(Display &display);
};
