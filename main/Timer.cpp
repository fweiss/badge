#include "Timer.h"

Timer::Timer() {
    this->group = (timer_group_t) 0;
    this->index = (timer_idx_t) 0;
}

void Timer::timerIsr(void *data) {
    int timer_idx = (int) data;
}

void Timer::start() {
    timer_start(group, index);
}
