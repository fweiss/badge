#pragma once

#include <stdio.h>
#include <stdint.h>

#include "esp_timer.h"

#include "MPU6050.hpp"

typedef struct {
	float ax, ay, az;
} MotionData;

typedef void (*MotionCallback)(MotionData motionData);

class Motion : private MPU6050 {
public:
	Motion();
	virtual ~Motion() {};

	void start();
	void setListeners(MotionCallback callback);
private:
	esp_timer_handle_t timer;
	MotionCallback motionCallback;

	static void timerCallback(void* arg);
	void setupSensor();
	void sample();
};

