#pragma once

#include <functional>

#include "esp_timer.h"

#include "BaseAnimationTask.h"

class TimerAnimationTask : public BaseAnimationTask {
public:
	TimerAnimationTask();
	virtual ~TimerAnimationTask() {}
	virtual void start() override;
	virtual void setIntervalSecs(float secs) override;
	virtual void setCallback(void lambda(void)) override;
private:
	esp_timer_handle_t timer;
    std::function<void(void)> func;
    static void taskCode(void*);
};
