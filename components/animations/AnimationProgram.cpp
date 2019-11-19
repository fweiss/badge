#include "AnimationProgram.h"

#include "esp_log.h"

static const char* TAG = "PROGRAM";

AnimationProgram::AnimationProgram() : programs() {

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
    this->index = index;
}
