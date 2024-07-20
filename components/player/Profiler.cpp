#include "Profiler.h"

#include "esp_log.h"

static const char* TAG = "Profiler";

Profiler::Profiler(bool enable) {
	esp_err_t esp_err;
	if (enable) {
		ESP_LOGI(TAG, "started");
	} else {
		ESP_LOGI(TAG, "not started");
	}
	reset();

	const esp_timer_create_args_t create_args= {
        .callback = &Profiler::callback,
        .arg = this,
        .dispatch_method = ESP_TIMER_TASK,
        .name = "profiler timer",
        .skip_unhandled_events = true,
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

void Profiler::startTime() {
	lastStartTime = esp_timer_get_time();
}

void Profiler::stopTime() {
	runTime += esp_timer_get_time() - lastStartTime;
	lastStartTime = 0;
	samples++;
}

void Profiler::dump() {
    if (samples == 0) {
	    ESP_LOGI(TAG, "samples: none");
    } else {
        uint64_t average = runTime / samples;
        ESP_LOGI(TAG, "samples: %lld run time: %lld average (us): %lld", samples, runTime, average);
    }
	reset();
}

void Profiler::callback(void* arg) {
	((Profiler*)arg)->dump();
}

void Profiler::reset() {
	lastStartTime = 0;
	samples = 0;
	runTime = 0;
}
