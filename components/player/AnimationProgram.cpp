#include "AnimationProgram.h"

#include "esp_log.h"

static const char* TAG = "AnimationProgram";

AnimationProgram::AnimationProgram(BaseAnimationTask &animator)
	: programs(), animator(animator), profiler(false) {

}

void AnimationProgram::putAnimation(uint8_t index, Animation *animation) {
    programs[index] = animation;
}

void AnimationProgram::drawFrame(Frame &frame) {
	profiler.startTime();
    // fixme check index
    programs[index]->drawFrame(frame);
    profiler.stopTime();
}

// The frame period is defined in each animations constructor, or the default from the Animation base class
void AnimationProgram::setProgram(uint8_t index) {
    ESP_LOGI(TAG, "set program %d", index);
    auto search = programs.find(index);
    if (search == programs.end()) {
        ESP_LOGW(TAG, "set program ignored: out of range: 0-%d", programs.size() - 1);
    } else {
        this->index = index;
        auto framePeriodMillis = search->second->getFramePeriodMillis();
        animator.setIntervalSecs(framePeriodMillis / 1000.0);
    }
}

const Animation *AnimationProgram::getCurrentAnimation() {
    return programs[index];
}
