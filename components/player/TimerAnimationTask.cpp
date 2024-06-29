#include "TimerAnimationTask.h"

#include "esp_log.h"

static const char* TAG = "TimerAnimationTask";

void TimerAnimationTask::taskCode(void* arg) {
    ((TimerAnimationTask*)arg)->func();
}

TimerAnimationTask::TimerAnimationTask() {
	esp_err_t esp_err;
	esp_err = esp_timer_init()	;
	if (esp_err != ESP_OK) {
		ESP_LOGW(TAG, "esp_timer_init failed: %d", esp_err);
	}
	// todo deinit in destructor?

	const esp_timer_create_args_t create_args = {
			.callback = &taskCode,
			.arg = this,
			.dispatch_method = ESP_TIMER_TASK,
			.name = "fairy"
	};
	esp_err = esp_timer_create(&create_args, &this->timer);
	if (esp_err != ESP_OK) {
		ESP_LOGE(TAG, "esp_timer_create failed: %d", esp_err);
		return;
	}
	// todo disable?
	ESP_LOGI(TAG, "created");

}
void TimerAnimationTask::start() {
}

void TimerAnimationTask::setCallback(void lambda(void)) {
	this->func = lambda;

}
void TimerAnimationTask::setIntervalSecs(float secs) {
	esp_err_t esp_err;
	esp_err = esp_timer_stop(this->timer);
	if (esp_err != ESP_OK) {
		ESP_LOGW(TAG, "esp_timer_stop failed %d", esp_err);
	}

	uint64_t period = secs * 1000000.;
	esp_err = esp_timer_start_periodic(this->timer, period);
	if (esp_err != ESP_OK) {
		ESP_LOGE(TAG, "esp_timer_start_periodic failed: %d", esp_err);
	}
}

