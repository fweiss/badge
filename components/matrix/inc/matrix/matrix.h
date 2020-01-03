#pragma once

#include <stdint.h>

#include "driver/rmt.h"

class Matrix {
public:
    Matrix(gpio_num_t gpioPin, size_t size);
    ~Matrix();

    const size_t bytesPerPixel = 3;

    void setPixelRgb(uint32_t index, uint8_t r, uint8_t g, uint8_t b);
    void show();
private:
    const rmt_channel_t channel = RMT_CHANNEL_0;
    size_t size;
    uint8_t *grbPixels;

    void sendReset();
};
