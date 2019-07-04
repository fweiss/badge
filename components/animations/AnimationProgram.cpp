#include "AnimationProgram.h"

#include "esp_log.h"

#define ANIPROG_TAG "ANIPROGRAM"

AnimationProgram::AnimationProgram() : programs() {

}

void AnimationProgram::putAnimation(uint8_t index, Animation *animation) {
    programs[index] = animation;
}

void AnimationProgram::drawFrame() {
    programs[index]->drawFrame();
}

void AnimationProgram::setProgram(uint8_t index) {
    ESP_LOGI(ANIPROG_TAG, "set program %d", index);
    this->index = index;
}
