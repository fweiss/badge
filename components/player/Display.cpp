#include "Display.h"

Display::Display(gpio_num_t gpio) : matrix(gpio, 64) {
    this->brightness = 25;
}

void Display::reset() {
    matrix.sendReset();
}

void Display::clear() {
    for (int i=0; i<64; i++) {
        setPixel(i, 0, 0, 0);
    }

}

void Display::setPixel(uint16_t p, uint32_t color) {
//    uint8_t r = color & 0xff;
//    uint8_t g = (color >> 8) & 0xff;
//    uint8_t b = (color >> 16) & 0xff;
    uint8_t r = (color >> 16) & 0xff;
    uint8_t g = (color >> 8) & 0xff;
    uint8_t b = color & 0xff;
    this->setPixel(p, r, g, b);
}

void Display::setPixel(uint16_t p, uint8_t r, uint8_t g, uint8_t b) {
    this->setPixelRgb(p, r, g, b);
}

void Display::setPixelRgb(uint16_t p, uint8_t r, uint8_t g, uint8_t b) {
    uint8_t scaledRed = (r * brightness) / 100;
    uint8_t scaledGreen = (g * brightness) / 100;
    uint8_t scaledBlue = (b * brightness) / 100;
    if (p < pixelCount) {
        matrix.setPixelRgb(p, scaledRed, scaledGreen, scaledBlue);
    }
    // todo exception
}

void Display::update() {
    matrix.show();
}

void Display::show() {
    matrix.show();
}

void Display::setBrightness(uint8_t brightness) {
    this->brightness = brightness;
}

uint32_t Display::getPixel(uint16_t index) {
    return matrix.getPixelRgb(index);
}
