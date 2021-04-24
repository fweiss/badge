#include "MPU6050.hpp"

#include "esp_log.h"

static const char* TAG = "MPU6050";

namespace regs {
	constexpr uint8_t PWR_MGMT1             = (0x6B);
	constexpr uint8_t PWR1_DEVICE_RESET_BIT = (7);

	constexpr uint8_t ACCEL_XOUT_H     = (0x3B);  // [15:0]
	constexpr uint8_t ACCEL_XOUT_L     = (0x3C);
	constexpr uint8_t ACCEL_YOUT_H     = (0x3D);  // [15:0]
	constexpr uint8_t ACCEL_YOUT_L     = (0x3E);
	constexpr uint8_t ACCEL_ZOUT_H     = (0x3F);  // [15:0]
	constexpr uint8_t ACCEL_ZOUT_L     = (0x40);
}

#define E(x) (esp_err = (x))

MPU6050::MPU6050(uint8_t busAddress) : I2CDevice(busAddress) {
	this->setAccelFactor(0);
}

void MPU6050::reset() {
	__attribute__((unused)) esp_err_t esp_err;

	E( writeBit(regs::PWR_MGMT1, 1, regs::PWR1_DEVICE_RESET_BIT) );
}

esp_err_t MPU6050::readAccelerometer(accel_t *accel) {
	esp_err_t esp_err;

	int timeout = 10;
	uint8_t reg = regs::ACCEL_XOUT_H;
	uint8_t buffer[6];

    E( readBytes(reg, buffer, sizeof(buffer), timeout) );

    accel->x = buffer[0] << 8 | buffer[1];
    accel->y = buffer[2] << 8 | buffer[3];
    accel->z = buffer[4] << 8 | buffer[5];

	return esp_err;
}

esp_err_t MPU6050::setAccelFullScale(accel_fs_t fsr) {
	esp_err_t esp_err;

	const uint8_t reg = 0x1C;
	uint8_t AFS_SEL_2G = 0x00;
	uint8_t AFS_SEL_4G = 0x01;
	uint8_t AFS_SEL_F_B = 3;
	uint8_t AFS_SEL_F_L = 2;

	const uint8_t data = AFS_SEL_2G;
	const uint8_t length = AFS_SEL_F_L;
	const uint8_t offset = AFS_SEL_F_B;

    E( writeBits(reg, data, offset, length) );

	setAccelFactor(fsr);
	return esp_err;
}

