#include "AnimationProgram.h"

#include "esp_log.h"

static const char* TAG = "AnimationProgram";

AnimationProgram::AnimationProgram(Timer &animator) : programs(), animator(animator) {

}

void AnimationProgram::putAnimation(uint8_t index, Animation *animation) {
    programs[index] = animation;
}

void AnimationProgram::drawFrame() {
    // fixme check index
    programs[index]->drawFrame();
}

void AnimationProgram::setProgram(uint8_t index) {
    ESP_LOGI(TAG, "set program %d", index);
    if (index < programs.size()) {
        this->index = index;
        animator.setIntervalSecs(index == 4 || index == 5 ? .3 : .03);
    } else {
        ESP_LOGW(TAG, "set program ignored: out of range: 0-%d", programs.size() - 1);
    }
}
