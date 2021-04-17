#include "inc/motion/Motion.hpp"

#include "esp_log.h"

static const char* TAG = "MOTION";

Motion::Motion() {
	esp_err_t esp_err;
	bool enable = true;
	const esp_timer_create_args_t create_args= {
			.callback = &Motion::callback,
			.arg = this,
			.dispatch_method = ESP_TIMER_TASK,
			.name = "motion timer"
	};
	esp_err = esp_timer_create(&create_args, &timer);
	if (esp_err != ESP_OK) {
		ESP_LOGW(TAG, "esp_timer_create: %d", esp_err);
	}
	uint64_t dumpInterval = 2 * 1000 * 1000;

	if (enable) {
		esp_err = esp_timer_start_periodic(timer, dumpInterval);
		if (esp_err != ESP_OK) {
			ESP_LOGW(TAG, "esp_timer_start_periodic: %d", esp_err);
		}
	}

}

void Motion::start() {
    ESP_LOGI(TAG, "initializing");
}

void Motion::sample() {
	ESP_LOGI(TAG, "sample");
}

void Motion::callback(void* arg) {
	((Motion*)arg)->sample();
}

