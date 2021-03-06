#pragma once

#include <functional>

#include "esp_system.h"
#include "soc/timer_group_struct.h"
#include "driver/timer.h"

class Timer {
public:
    Timer();
    virtual ~Timer() {}

    void setCallback(void lambda(void));
    void start();
    void setIntervalSecs(float secs);

    static void timerIsr(void *data); // nice if it were private
private:
    timer_group_t group;
    timer_idx_t index;
    double timer_scale;
    static std::function<void(void)> func;
};
