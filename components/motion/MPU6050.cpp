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

esp_err_t MPU6050::setSleep(bool sleep) {
	esp_err_t esp_err;
	const uint8_t reg = 0x6B;
	const uint8_t data = sleep;
	const uint8_t offset = 6;

	E( writeBit(reg, data, offset) );

	return esp_err;
}

esp_err_t MPU6050::setClockSource(uint8_t source) {
	esp_err_t esp_err;

	const uint8_t reg = 0x6B;
	const uint8_t data = source;
	const uint8_t offset = 0;
	const uint8_t length = 3;
	E( writeBits(reg, data, offset, length) );

	return esp_err;
}

esp_err_t MPU6050::readAccelerometer(accel_t *accel) {
	esp_err_t esp_err;

	uint8_t reg = regs::ACCEL_XOUT_H;
	uint8_t buffer[6];

    E( readBytes(reg, buffer, sizeof(buffer)) );

	// at fullscale 1/4g, 0x20->1.0, 0xE0->-1.0
	// with aceelFactor accelFactor = (2 << fsr) / (float)32768
	// fake=0x20/0xE0 0x2000=8192
	// fake=0x40/0xC0 0x4000=16384
	// fake=0x7FFF/0x8000 32768
	// fsr=0  2G 16384 accel=0.50
	// fsr=1  4G  8192 aceel=1.00
	// fsr=2  8G  4096 accel=2.00
	// fsr=3 16G  2048 accel=4.00

    accel->x = buffer[0] << 8 | buffer[1];
    accel->y = buffer[2] << 8 | buffer[3];
    accel->z = buffer[4] << 8 | buffer[5];

	return esp_err;
}

esp_err_t MPU6050::setAccelFullScale(accel_fs_t fsr) {
	esp_err_t esp_err;

	const uint8_t reg = 0x1C;
	__attribute__((unused)) uint8_t AFS_SEL_2G = 0x00;
	__attribute__((unused)) uint8_t AFS_SEL_4G = 0x01;
	uint8_t AFS_SEL_F_B = 3;
	uint8_t AFS_SEL_F_L = 2;

	const uint8_t data = fsr;
	const uint8_t length = AFS_SEL_F_L;
	const uint8_t offset = AFS_SEL_F_B;

    E( writeBits(reg, data, offset, length) );

	setAccelFactor(fsr);
	return esp_err;
}

// for testing
uint8_t MPU6050::getAccelFullScale() {
	const uint8_t reg = 0x1C;
	uint8_t buf;
	readByte(reg, &buf);
	return buf;
}

esp_err_t MPU6050::performAccelSelfTest() {
	esp_err_t esp_err = ESP_OK;
	uint8_t reg = 0x1C;
	uint8_t data = 0x07;
	uint8_t offset = 5;
	uint8_t length = 3;

	setAccelFullScale(3);

	E( writeBits(reg, data, offset, length) );

	uint8_t buffer[4];
	uint8_t selftest_reg = 0x0d;
	E( readBytes(selftest_reg, buffer, sizeof(buffer)) );
	uint8_t xa_test = ((buffer[0] >> 3) & 0x1C) | ((buffer[3] >> 4) & 0x03);
	uint8_t ya_test = ((buffer[1] >> 3) & 0x1C) | ((buffer[3] >> 2) & 0x03);
	uint8_t za_test = ((buffer[2] >> 3) & 0x1C) | ((buffer[3] >> 0) & 0x03);
	ESP_LOGI(TAG, "accel self-test %d %d %d", xa_test, ya_test, za_test);

	return esp_err;
}

void MPU6050::setDigitalLowPassFilter(int data) {
	__attribute__((unused)) esp_err_t esp_err;

	const uint8_t reg = 0x1a;
	const uint8_t offset = 0;
	const uint8_t length = 3;

	E( writeBits(reg, data, offset, length) );
}
