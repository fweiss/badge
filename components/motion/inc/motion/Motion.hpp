#pragma once

#include <stdio.h>
#include <stdint.h>

#include "esp_timer.h"

#include "I2CDevice.hpp"

class Motion : private I2CDevice {
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
