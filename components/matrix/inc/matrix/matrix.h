#pragma once

#include "driver/rmt_tx.h"

class Matrix {
public:
    Matrix(gpio_num_t gpioPin, size_t size);
    ~Matrix();

    const size_t bytesPerPixel = 3;

    const uint32_t tickResolutionHz = 10 * 1000 * 1000;
    constexpr uint16_t fromMicros(float micros) {
        return micros * tickResolutionHz / 1000. / 1000.;
    }

    void setPixelRgb(uint32_t index, uint8_t r, uint8_t g, uint8_t b);
    uint32_t getPixelRgb(uint16_t index);

    void show();
    void sendReset();
private:
    rmt_channel_handle_t channel;
    rmt_encoder_handle_t encoder;
    rmt_encoder_handle_t resetEncoder;
    size_t size;
    uint8_t *grbPixels;

    void createResetEncoder();
};
