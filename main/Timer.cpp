#include "Timer.h"

std::function<void(void)> Timer::func = [](){}; // dummy function

Timer::Timer() {
    this->group = (timer_group_t) 0;
    this->index = (timer_idx_t) 0;

    bool auto_reload = true;

    // initialize the timer configuration
    timer_config_t config;
    config.divider = 16;
    config.counter_dir = TIMER_COUNT_UP;
    config.counter_en = TIMER_PAUSE;
    config.alarm_en = TIMER_ALARM_EN;
    config.intr_type = TIMER_INTR_LEVEL;
    config.auto_reload = auto_reload;
    timer_init(TIMER_GROUP_0, this->index, &config);

    // initialize the timer counter
    timer_set_counter_value(TIMER_GROUP_0, this->index, 0x00000000ULL);
}

void Timer::setCallback(std::function<void(void)> _func) {
    // todo private, per timer
    func = _func;
}

void Timer::timerIsr(void *data) {
    int timer_idx = (int) data;
    TIMERG0.int_clr_timers.t0 = 1; // clear the interrupt
    TIMERG0.hw_timer[timer_idx].config.alarm_en = TIMER_ALARM_EN; // retrigger alarm
    func();
}

void Timer::start() {
    timer_start(group, index);
}
