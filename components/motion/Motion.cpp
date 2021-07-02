#include "inc/motion/Motion.hpp"

#include "esp_log.h"
#include <stdlib.h>
#include <math.h>


static const char* TAG = "MOTION";

#define E(x) (esp_err = (x))

Motion::Motion() : MPU6050(0x68) {
	esp_err_t esp_err;
	bool enable = true;
	this->motionCallback = [](MotionData){};

	const esp_timer_create_args_t create_args= {
		.callback = &Motion::timerCallback,
		.arg = this,
		.dispatch_method = ESP_TIMER_TASK,
		.name = "motion timer"
	};
	esp_err = esp_timer_create(&create_args, &timer);
	if (esp_err != ESP_OK) {
		ESP_LOGW(TAG, "esp_timer_create: %d", esp_err);
	}
	uint64_t dumpInterval = 200 * 1000;

	if (enable) {
		esp_err = esp_timer_start_periodic(timer, dumpInterval);
		if (esp_err != ESP_OK) {
			ESP_LOGW(TAG, "esp_timer_start_periodic: %d", esp_err);
		}
	}
}

void Motion::setListeners(MotionCallback motionCallback) {
	this->motionCallback =  motionCallback;
}

void Motion::start() {
    ESP_LOGI(TAG, "initializing");
	setupSensor();
}

// float scale(int16_t reg) {
// 	// const float s = 16385; // 0 2g
// 	const float s = (float)4 / 32767; // 4g
// 	return reg * s;
// }

void Motion::sample() {
	__attribute__((unused)) esp_err_t esp_err;

	accel_t accel;
	E( readAccelerometer(&accel) );
	float accelFactor = getAccelFactor();
	float fx = accel.x * accelFactor;
	float fy = accel.y * accelFactor;
	float fz = accel.z * accelFactor;
	// printf("accel: [%+6.2f %+6.2f %+6.2f ] (g)\n", fx, fy, fz);

	const MotionData motionData = {
		fx, fy, fz
	};
	this->motionCallback(motionData);
}

void Motion::timerCallback(void* arg) {
	((Motion*)arg)->sample();
}

void Motion::setupSensor() {
	esp_err_t esp_err;
	reset();
	vTaskDelay(500 / portTICK_PERIOD_MS);
	setSleep(false);
	setClockSource(1); // 1 = PLL with X axis gyroscope reference
	// setGyroFullScale(GYRO_FS_500DPS)
	// performAccelSelfTest();
	esp_err = setAccelFullScale(2); // 0=2g, 1=4g, 2=8g, 3=16g
	printf("accelFactor: %d, %f\n", esp_err, getAccelFactor());
	uint8_t fsr;
	fsr = getAccelFullScale();
	printf("fsr %x\n", fsr);
	// setDigitalLowPassFilter(DLPF_5HZ)
	// setSampleRate(100)
}
