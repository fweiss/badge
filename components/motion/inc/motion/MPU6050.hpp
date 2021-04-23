#pragma once

#include "I2CDevice.hpp"

typedef struct Accel {
	uint16_t x;
	uint16_t y;
	uint16_t z;
} accel_t;

class MPU6050 : private I2CDevice {
public:
	MPU6050(uint8_t busAddress);
	virtual ~MPU6050() {}
public:
	void reset();
	esp_err_t readAccelerometer(accel_t *accel);
};
