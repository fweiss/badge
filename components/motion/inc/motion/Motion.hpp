#pragma once

#include "esp_timer.h"

class Motion {
public:
	Motion();
	virtual ~Motion() {};

	void start();
private:
	esp_timer_handle_t timer;
	static void callback(void* arg);
	void sample();
};
