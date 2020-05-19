#pragma once

#include "BitmapAnimation.h"

class Tween : public BitmapAnimation {
public:
	Tween(Display &display);

	void drawFrame(uint16_t frameIndex) override;
private:
    static BitmapAnimation::Frames frames;
};
