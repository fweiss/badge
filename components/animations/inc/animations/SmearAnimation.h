#pragma once

#include "display.h"
#include "Animation.h"

class SmearAnimation : public Animation {
private:
//	Display *display;
	uint8_t r;
protected:
public:
//	SmearAnimation(led_strip_t *ledStrip);
	SmearAnimation(Display &display);
//	SmearAnimation();
	void drawFrame();
};
