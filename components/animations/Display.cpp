#include "display.h"
#include "led_strip/led_strip.h"

Display::Display(gpio_num_t gpio) : matrix(gpio, 64) {
//    rmt_channel_t rmt_channel = RMT_CHANNEL_1;
//    int rmt_interrupt_num = 19U;
//    bool showing_buf_1 = false;
//    SemaphoreHandle_t access_semaphore = xSemaphoreCreateBinary();
//
//    ledStrip = new led_strip_t{
//        RGB_LED_TYPE_WS2812, pixelCount,
//        rmt_channel,
//        rmt_interrupt_num, gpio,
//        showing_buf_1,
//        led_strip_buf_1,
//        led_strip_buf_2,
//        access_semaphore};
//    bool ok = led_strip_init(ledStrip);
//    (void)ok; // fixme log an error
    this->brightness = 25;
}

//Display::Display(led_strip_t *ledStrip) {
//    this->ledStrip = ledStrip;
//    this->brightness = 50;
//}

void Display::clear() {

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
//        led_strip_set_pixel_rgb(ledStrip, p, scaledRed, scaledGreen, scaledBlue);
        matrix.setPixelRgb(p, scaledRed, scaledGreen, scaledBlue);
    }
    // todo exception
}

void Display::update() {
    matrix.show();
//    led_strip_show(ledStrip);
}

void Display::show() {
    matrix.show();
//    led_strip_show(ledStrip);
}

void Display::setBrightness(uint8_t brightness) {
    this->brightness = brightness;
}

uint32_t Display::getPixel(uint16_t index) {
    return matrix.getPixelRgb(index);
}
