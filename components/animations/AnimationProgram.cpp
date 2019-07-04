#include "AnimationProgram.h"

AnimationProgram::AnimationProgram() : programs() {

}

void AnimationProgram::putAnimation(uint8_t index, Animation *animation) {
    programs[index] = animation;
}

void AnimationProgram::drawFrame() {
    programs[0]->drawFrame();
}
