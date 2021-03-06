#pragma once

#include "freertos/FreeRTOS.h"
#include "led_strip/led_strip.h"
#include "matrix/matrix.h"

class Display {
public:
    Display(gpio_num_t gpio);
//    Display(led_strip_t *ledString);

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
    struct led_color_t led_strip_buf_1[64];
    struct led_color_t led_strip_buf_2[64];
    struct led_strip_t *ledStrip;
    uint8_t brightness;
    Matrix matrix;
};
