#pragma once

#include <stdio.h>
#include <stdint.h>

#include "driver/i2c.h"

class I2CDevice {
public:
	I2CDevice();
	virtual ~I2CDevice() {}

	esp_err_t readBytes(uint8_t devAddr, uint8_t regAddr, size_t length, uint8_t *data, int32_t timeout);
	esp_err_t writeBit(uint8_t reg, uint8_t bit, uint8_t value);
};
