#include "Timer.h"

std::function<void(void)> Timer::func = [](){}; // dummy function

Timer::Timer() {
    this->group = (timer_group_t) 0;
    this->index = (timer_idx_t) 0;

    bool auto_reload = true;
    double timer_interval_sec = 0.030;
    uint32_t timer_divider = 16.0;
    double timer_scale = (TIMER_BASE_CLK / timer_divider);

    // initialize the timer configuration
    timer_config_t config;
    config.divider = 16;
    config.counter_dir = TIMER_COUNT_UP;
    config.counter_en = TIMER_PAUSE;
    config.alarm_en = TIMER_ALARM_EN;
    config.intr_type = TIMER_INTR_LEVEL;
    config.auto_reload = auto_reload;
    timer_init(TIMER_GROUP_0, this->index, &config);

    // initialize the timer
    timer_set_counter_value(TIMER_GROUP_0, this->index, 0x00000000ULL);
    timer_set_alarm_value(TIMER_GROUP_0, this->index, timer_interval_sec * timer_scale);

    // setup alarm isr
    timer_enable_intr(TIMER_GROUP_0, this->index);
    int intr_alloc_flags = ESP_INTR_FLAG_IRAM;
    timer_isr_handle_t *handle = NULL;
    timer_isr_register(TIMER_GROUP_0, this->index, Timer::timerIsr, (void *) this->index, intr_alloc_flags, handle);
}

void Timer::setCallback(void func(void)) {
    // todo private, per timer
    this->func = func;
}

void IRAM_ATTR Timer::timerIsr(void *data) {
    int timer_idx = (int) data;
    TIMERG0.int_clr_timers.t0 = 1; // clear the interrupt
    TIMERG0.hw_timer[timer_idx].config.alarm_en = TIMER_ALARM_EN; // retrigger alarm
    func();
}

void Timer::start() {
    timer_start(group, index);
}
