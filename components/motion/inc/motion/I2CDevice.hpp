#pragma once

#include <stdio.h>
#include <stdint.h>

#include "driver/i2c.h"

class I2CDevice {
public:
	I2CDevice(uint8_t address);
	virtual ~I2CDevice();

	esp_err_t readBytes(uint8_t reg, uint8_t *data, size_t length, int32_t timeout);

	esp_err_t writeBit(uint8_t reg, uint8_t data, uint8_t offset);
	esp_err_t writeBits(uint8_t reg, uint8_t data, uint8_t offset, uint8_t length);

	esp_err_t writeBytes(uint8_t reg, uint8_t *data, size_t length);
private:
	i2c_port_t port;
	uint8_t address;
	TickType_t ticks;
};
