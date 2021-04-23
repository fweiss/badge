#pragma once

#include <stdio.h>
#include <stdint.h>

#include "esp_timer.h"

#include "MPU6050.hpp"

class Motion : private MPU6050 {
public:
	Motion();
	virtual ~Motion() {};

	void start();
private:
	esp_timer_handle_t timer;

	static void callback(void* arg);
	void setupSensor();
	void sample();
};
