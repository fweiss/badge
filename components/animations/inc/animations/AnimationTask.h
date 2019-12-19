#pragma once

#include "Animation.h"

#include "freertos/task.h"
#include "freertos/semphr.h"

class AnimationTask {
public:
    AnimationTask();
    ~AnimationTask();

    void start();
    void setIntervalSecs(float secs);
    void setCurrentAnimantion(Animation *animation) { this->currentAnimation = animation; }
    void setCallback(void lambda(void));

protected:
    SemaphoreHandle_t semaphoreHandle;

//    TickType_t lastWakeTimeTicks;
    TickType_t currentIntervalTicks;
    Animation *currentAnimation;

    TaskHandle_t taskHandle;
    static void taskCode(void *parameters);
    void run();
};
