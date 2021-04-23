#include "I2CDevice.hpp"

#include "esp_log.h"

static const char* TAG = "I2CDEVICE";

#define I2C_MASTER_TX_BUF_DISABLE 0                           /*!< I2C master doesn't need buffer */
#define I2C_MASTER_RX_BUF_DISABLE 0                           /*!< I2C master doesn't need buffer */
#define I2C_MASTER_ACK_EN   true    /*!< Enable ack check for master */
#define I2C_MASTER_ACK_DIS  false   /*!< Disable ack check for master */

I2CDevice::I2CDevice() {
	esp_err_t esp_err;

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

esp_err_t I2CDevice::readBytes(uint8_t devAddr, uint8_t regAddr, size_t length, uint8_t *data, int32_t timeout) {
	int port = 0;
	int ticksToWait = 20;
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (devAddr << 1) | I2C_MASTER_WRITE, I2C_MASTER_ACK_EN);
    i2c_master_write_byte(cmd, regAddr, I2C_MASTER_ACK_EN);
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (devAddr << 1) | I2C_MASTER_READ, I2C_MASTER_ACK_EN);
    i2c_master_read(cmd, data, length, I2C_MASTER_LAST_NACK);
    i2c_master_stop(cmd);
    esp_err_t err = i2c_master_cmd_begin(port, cmd, (timeout < 0 ? ticksToWait : pdMS_TO_TICKS(timeout)));
    i2c_cmd_link_delete(cmd);
    return 0;
}

esp_err_t I2CDevice::writeBit(uint8_t reg, uint8_t bit, uint8_t value) {
	return 0;
}


