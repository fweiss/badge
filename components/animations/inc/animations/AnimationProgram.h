#pragma once

#include <map>

#include "Animation.h"

class AnimationProgram {
public:
    AnimationProgram();
    virtual ~AnimationProgram() {};

    void drawFrame();
    void putAnimation(uint8_t index, Animation *animation);
    void setProgram(uint8_t index);
private:
    std::map<uint8_t,Animation*> programs;
};
