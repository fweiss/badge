#include "inc/motion/Motion.hpp"

#include "esp_log.h"

static const char* TAG = "MOTION";

#define E(x) (esp_err = (x))

Motion::Motion() : MPU6050(0x68) {
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
//    setupSensor();
}

void Motion::sample() {
	esp_err_t esp_err;

	ESP_LOGI(TAG, "sample");

	accel_t accel;
	E( readAccelerometer(&accel) );
	ESP_LOGI(TAG, "accel xyz %d %d %d", accel.x, accel.y, accel.z);

}

namespace regs {
	constexpr uint8_t PWR_MGMT1             = (0x6B);
	constexpr uint8_t PWR1_DEVICE_RESET_BIT = (7);
}

void Motion::callback(void* arg) {
	((Motion*)arg)->sample();
}

void Motion::setupSensor() {
	reset();
	// delay
	// setSleep(false)
	// setClockSource(CLOCK_PLL)
	// setGyroFullScale(GYRO_FS_500DPS)
	// setAccelFullScale(ACCEL_FS_4G)
	// setDigitalLowPassFilter(DLPF_5HZ)
	// setSampleRate(100)
}

