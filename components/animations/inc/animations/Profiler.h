#pragma once

#include "esp_timer.h"

class Profiler {
public:
	Profiler(bool enable);
	void startTime();
	void stopTime();
private:
	uint64_t lastStartTime;
	uint64_t runTime;
	uint64_t samples;
	esp_timer_handle_t timer;
	void reset();
	void dump();
	static void callback(void* arg);
};
