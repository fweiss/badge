#pragma once

#include "freertos/FreeRTOS.h"
#include "matrix/matrix.h"

class Display {
public:
    Display(gpio_num_t gpio);

    void clear();
    void update();
    void show();
    void setBrightness(uint8_t brightness);
    void setPixelRgb(uint16_t p, uint8_t r, uint8_t g, uint8_t b);
    void setPixel(uint16_t p, uint8_t r, uint8_t g, uint8_t b);
    void setPixel(uint16_t p, uint32_t color);
    uint32_t getPixel(uint16_t p);

    const uint16_t pixelCount = 64;
private:
    uint8_t brightness;
    Matrix matrix;
};
