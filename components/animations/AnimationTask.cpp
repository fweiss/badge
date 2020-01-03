#include "AnimationTask.h"

#include "esp_log.h"

static const char *TAG = "AniumationTask";

AnimationTask::AnimationTask() {
    semaphoreHandle = xSemaphoreCreateBinary();
    currentIntervalTicks = 300 / portTICK_PERIOD_MS;
}

AnimationTask::~AnimationTask() {
    // there should be nothing blocked
    vSemaphoreDelete(semaphoreHandle);
}

void AnimationTask::start() {
    static char name[] = "animator task";
    uint16_t stackDepth = 8096;
    UBaseType_t priority = tskIDLE_PRIORITY + 4;
    BaseType_t status = xTaskCreate(AnimationTask::taskCode, name, stackDepth, this, priority, &taskHandle);
    if (status != pdPASS) {
        ESP_LOGE(TAG, "Create task failed: %d", status);
    }
    // TODO check taskHandle
}

void AnimationTask::setIntervalSecs(float secs) {
    currentIntervalTicks = (TickType_t)(secs / 1000 / portTICK_PERIOD_MS);

    // signal the animation loop that a change is requested
    BaseType_t success = xSemaphoreGive(semaphoreHandle);
    if (! success) {
        ESP_LOGE(TAG, "Create semaphore failed: %d", success);
    }
}

void AnimationTask::taskCode(void *parameters) {
    ((AnimationTask*)parameters)->run();
}

void AnimationTask::run() {
    for (;;) {

        // call the animation drawframe function
//            ESP_LOGI(TAG, "drawing...");
        func();

        // block waiting for an animation change or the current animation interval
        // this allows changes to occur without waiting for the interval to expire,
        // such as would be the case with vTaskDelayUntil()
        // we may want to use vTaskDelayUntil on a different task to provide more precise
        // timing
        BaseType_t notified = xSemaphoreTake(semaphoreHandle, currentIntervalTicks);
        if (notified) {
            // the animation task was interruoted
        } else {
            // the animation task interval expired
        }

        vTaskDelay(300 / portTICK_PERIOD_MS);

        //  check task status
    }
}
