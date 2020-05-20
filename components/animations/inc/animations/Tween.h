#pragma once

#include "BitmapAnimation.h"

class Tween : public BitmapAnimation {
public:
	Tween(Display &display);

	void drawFrame(uint16_t frameIndex) override;
	virtual void nextFrame() { frameIndex = (frameIndex + 1); } // let it wrap!
private:
    static BitmapAnimation::Frames frames;
};
