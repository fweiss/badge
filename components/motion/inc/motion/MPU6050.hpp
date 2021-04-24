#pragma once

#include "I2CDevice.hpp"

typedef struct Accel {
	int16_t x;
	int16_t y;
	int16_t z;
} accel_t;

typedef uint8_t accel_fs_t;

class MPU6050 : private I2CDevice {
public:
	MPU6050(uint8_t busAddress);
	virtual ~MPU6050() {}

	void reset();
	esp_err_t setAccelFullScale(accel_fs_t fsr);
	esp_err_t readAccelerometer(accel_t *accel);

	float getAccelFactor() { return accelFactor; }
	void setAccelFactor(accel_fs_t fsr) { accelFactor = (2 << fsr) / (float)32768; }
private:
	float accelFactor;
};
