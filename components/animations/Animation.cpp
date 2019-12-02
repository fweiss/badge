#include "Animation.h"

static const uint16_t defaultFramePeriodMillis = 30;

Animation::Animation(Display &display) : display(display), framePeriodMillis(defaultFramePeriodMillis) {
}

Animation::Animation(Display &display, uint16_t framePeriodMillis) : display(display), framePeriodMillis(framePeriodMillis) {
}
