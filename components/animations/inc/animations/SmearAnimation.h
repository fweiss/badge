#pragma once

#include "display.h"

class SmearAnimation {
private:
	Display *display;
	uint8_t r;
protected:
public:
	SmearAnimation(led_strip_t *ledStrip);
	SmearAnimation(Display* display);
	SmearAnimation();
	void drawFrame();
};
