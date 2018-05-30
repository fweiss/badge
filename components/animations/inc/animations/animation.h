#pragma once

#include "esp_system.h"
#include "led_strip/led_strip.h"

#include "CandyChaser.h"

#include "display.h"

class Animation {
private:
	uint8_t r;
	Display *display;
protected:
public:
	Animation(led_strip_t *ledStrip);
	Animation(Display *display);
	void drawFrame();
	led_strip_t *ledStrip;
};
