#include "AnimationProgram.h"

#include "esp_log.h"

static const char* TAG = "AnimationProgram";

AnimationProgram::AnimationProgram(BaseAnimationTask &animator)
	: programs(), animator(animator), profiler() {

}

void AnimationProgram::putAnimation(uint8_t index, Animation *animation) {
    programs[index] = animation;
}

void AnimationProgram::drawFrame() {
	profiler.startTime();
    // fixme check index
    programs[index]->drawFrame();
    profiler.stopTime();
}

// The frame period is defined in each animations constructor, or the default from the Animation base class
void AnimationProgram::setProgram(uint8_t index) {
    ESP_LOGI(TAG, "set program %d", index);
    if (index < programs.size()) {
        this->index = index;
        animator.setIntervalSecs((float)programs[index]->getFramePeriodMillis() / 1000.0);
    } else {
        ESP_LOGW(TAG, "set program ignored: out of range: 0-%d", programs.size() - 1);
    }
}

const Animation *AnimationProgram::getCurrentAnimation() {
    return programs[index];
}
