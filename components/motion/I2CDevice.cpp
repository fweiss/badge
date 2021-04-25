#include "I2CDevice.hpp"

#include "esp_log.h"

static const char* TAG = "I2CDEVICE";

#define I2C_MASTER_TX_BUF_DISABLE 0                           /*!< I2C master doesn't need buffer */
#define I2C_MASTER_RX_BUF_DISABLE 0                           /*!< I2C master doesn't need buffer */
#define I2C_MASTER_ACK_EN   true    /*!< Enable ack check for master */
#define I2C_MASTER_ACK_DIS  false   /*!< Disable ack check for master */

#define E(x) (esp_err = (x))

I2CDevice::I2CDevice(uint8_t address) {
	esp_err_t esp_err;

	this->port = 0;
	this->address = address;
	this->ticks = 1000;

	// ESP32 i2c0
	// MPU sda 21, scl 22
	int i2c_master_port = 0;
	// issue with designated initialer in c++11
	i2c_config_t conf;
	conf.mode = I2C_MODE_MASTER;
			conf.sda_io_num = GPIO_NUM_21;
			conf.sda_pullup_en = GPIO_PULLUP_ENABLE;
			conf.scl_io_num = GPIO_NUM_22;
			conf.scl_pullup_en = GPIO_PULLUP_ENABLE;
//	    .master.clk_speed = I2C_MASTER_FREQ_HZ,  // select frequency specific to your project
	    // .clk_flags = 0,          /*!< Optional, you can use I2C_SCLK_SRC_FLAG_* flags to choose i2c source clock here. */
	conf.master.clk_speed = 400000;
	esp_err = i2c_param_config(i2c_master_port, &conf);
    if (esp_err != ESP_OK) {
		ESP_LOGW(TAG, "i2c param: %d", esp_err);
    }

    esp_err = i2c_driver_install(i2c_master_port, conf.mode, I2C_MASTER_RX_BUF_DISABLE, I2C_MASTER_TX_BUF_DISABLE, 0);
}

I2CDevice::~I2CDevice() {
	// esp_err = i2c_driver_delete(i2c_port_ti2c_num)
}

esp_err_t I2CDevice::readBytes(uint8_t regAddr, uint8_t *data, size_t length) {
	esp_err_t esp_err;

    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (address << 1) | I2C_MASTER_WRITE, I2C_MASTER_ACK_EN);
    i2c_master_write_byte(cmd, regAddr, I2C_MASTER_ACK_EN);
    i2c_master_start(cmd); // switching to read
    i2c_master_write_byte(cmd, (address << 1) | I2C_MASTER_READ, I2C_MASTER_ACK_EN);
    i2c_master_read(cmd, data, length, I2C_MASTER_LAST_NACK);
    i2c_master_stop(cmd);
    // esp_err = i2c_master_cmd_begin(port, cmd, (timeout < 0 ? ticksToWait : pdMS_TO_TICKS(timeout)));
    esp_err = i2c_master_cmd_begin(port, cmd, ticks);
    i2c_cmd_link_delete(cmd);
    return esp_err;
}

esp_err_t I2CDevice::writeBytes(uint8_t reg, uint8_t *data, size_t length) {
	esp_err_t esp_err;
	i2c_cmd_handle_t cmd;

	cmd = i2c_cmd_link_create(); // create command link

	E( i2c_master_start(cmd) ); // start bit
	E( i2c_master_write_byte(cmd, (address << 1) | I2C_MASTER_WRITE, I2C_MASTER_ACK_EN) ); // slave address
    E( i2c_master_write_byte(cmd, reg, I2C_MASTER_ACK_EN) );
	E( i2c_master_write(cmd, data, length, I2C_MASTER_ACK_EN) ); // write data
	E( i2c_master_stop(cmd) ); // stop bit

	E( i2c_master_cmd_begin(port, cmd, ticks) ); // execute command

	(void)i2c_cmd_link_delete(cmd); //release resources

	return esp_err;
}

esp_err_t I2CDevice::writeBits(uint8_t reg, uint8_t data, uint8_t offset, uint8_t length) {
		esp_err_t esp_err;

		uint8_t buf;

		E( readBytes(reg, &buf, (size_t) 1) );

		// clever, but not very fast
		// can probably do at compile time for the register definitions
		const uint8_t mask = ((1 << (length + offset)) - 1) & ~((1 << (offset)) - 1);
		buf &= ~mask;
		buf |= (data << offset) & mask;

		E( writeBytes(reg, &buf, 1) );
		return esp_err;
}

esp_err_t I2CDevice::writeBit(uint8_t reg, uint8_t data, uint8_t offset) {
	return writeBits(reg, data, offset, 1);
}

