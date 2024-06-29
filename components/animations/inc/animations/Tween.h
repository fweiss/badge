#pragma once

#include "BitmapAnimation.h"

class Tween : public BitmapAnimation {
public:
    Tween();

	void drawFrame(uint16_t frameIndex) override;
    virtual void drawFrame(Frame &frame) override;
	virtual void nextFrame() { frameIndex = (frameIndex + 1) % 52; } // let it wrap!
private:
    static BitmapAnimation::Frames frames;
    std::vector<uint32_t> compositeFrame;
};
