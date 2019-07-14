#pragma once

#include "display.h"
#include "Animation.h"

class SmearAnimation : public Animation {
private:
	uint16_t r;
protected:
public:
	SmearAnimation(Display &display);
	void drawFrame() override;
};
