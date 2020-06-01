#pragma once

#include "Animation.h"
#include "BaseAnimationTask.h"

#include "freertos/task.h"
#include "freertos/semphr.h"

#include <functional>

class AnimationTask : public BaseAnimationTask {
public:
    AnimationTask();
    ~AnimationTask();

    void start();
    void setIntervalSecs(float secs) override;
    void setCurrentAnimantion(Animation *animation) { this->currentAnimation = animation; }
    void setCallback(void lambda(void)) { this->func = lambda; }

protected:
    SemaphoreHandle_t semaphoreHandle;

//    TickType_t lastWakeTimeTicks;
    TickType_t currentIntervalTicks;
    Animation *currentAnimation;
    std::function<void(void)> func;


    TaskHandle_t taskHandle;
    static void taskCode(void *parameters);
    void run();
};
