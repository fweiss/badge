#pragma once

#include "PathAnimation.h"
#include "CandyChaser.h"

class MeteorShowerAnimation : public PathAnimation {
private:
protected:
public:
	MeteorShowerAnimation(Display &display);
	void drawFrame();
};
