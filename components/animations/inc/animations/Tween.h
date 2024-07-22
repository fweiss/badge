#pragma once

#include "BitmapAnimation.h"

class Tween : public BitmapAnimation {
public:
    Tween();

    virtual void drawFrame(Frame &frame) override;
	virtual void nextFrame() override;

    void pushFrame(std::vector<uint32_t> &frame);
    void drawFrame(Frame &frame, size_t offset);
private:
    static BitmapAnimation::Frames frames;
    std::vector<uint32_t> compositeFrame;
    void composeText(std::vector<uint32_t> &target, std::vector<std::vector<uint32_t>> &frames);

    uint16_t backgroundBrightness;
    uint32_t backgroundColor = 0x20202020   ;
    uint16_t foregrundBrightness;
    uint32_t foregroundColor= 0xffffffff;
};
