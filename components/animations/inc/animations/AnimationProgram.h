#pragma once

#include <map>

#include "Animation.h"
#include "AnimationTask.h"
#include "Profiler.h"

class AnimationProgram {
public:
    AnimationProgram(BaseAnimationTask &animator);
    virtual ~AnimationProgram() {};

    void drawFrame();
    void putAnimation(uint8_t index, Animation *animation);
    void setProgram(uint8_t index);
    const Animation *getCurrentAnimation();

private:
    std::map<uint8_t,Animation*> programs;
    uint8_t index = 0;
    BaseAnimationTask &animator;
    Profiler profiler;
};
