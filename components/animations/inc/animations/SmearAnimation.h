#pragma once

#include "Animation.h"

class SmearAnimation : public Animation {
private:
    uint16_t r;
protected:
public:
    SmearAnimation();
    virtual ~SmearAnimation() {}

    void drawFrame(Frame& frame) override;
};
