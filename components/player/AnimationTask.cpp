#include "AnimationTask.h"

#include "esp_log.h"

static const char *TAG = "AniumationTask";

AnimationTask::AnimationTask() {
    // note that the semaphore is in the "taken" state
    // we expect setIntervalSecs() to "give" the semaphore
    // nonetheless, we rely on xSemaphoreTake() timeout to pace the animation
    // however, start() must be after the first call to setIntervalSecs()
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
    BaseType_t coreId = 1; // assume that BT runs on core 0
    BaseType_t status = xTaskCreatePinnedToCore(AnimationTask::taskCode, name, stackDepth, this, priority, &taskHandle, coreId);
    if (status != pdPASS) {
        ESP_LOGE(TAG, "Create task failed: %d", status);
    }
    // TODO check taskHandle
}

void AnimationTask::setIntervalSecs(float secs) {
    currentIntervalTicks = (TickType_t)(secs * 1000 / portTICK_PERIOD_MS);

    ESP_LOGI(TAG, "requested %f sec, got %lu ticks", secs, currentIntervalTicks);

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
        // block waiting for an animation change or the current animation interval
        // this allows changes to occur without waiting for the interval to expire,
        // such as would be the case with vTaskDelayUntil()
        // we may want to use vTaskDelayUntil on a different task to provide more precise
        // timing
        BaseType_t notified = xSemaphoreTake(semaphoreHandle, currentIntervalTicks);
        if (notified) {
            // the animation task was interruoted
            // this is expected when the interval is changed
            ESP_LOGI(TAG, "animation task interrupted");
        } else {
            // the animation task interval expired
            // this is normal and requests the animation to be updated
        }

        func(); // call the animation update function
    }
}
